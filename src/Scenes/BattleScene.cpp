//
// Created by Gs0n 25-3-2.
//

#include "Scenes/BattleScene.hpp"

namespace Util {
    void BattleScene::Init(std::shared_ptr<Core::Context> context) {
        m_Animation = std::make_shared<AnimationSpace>(
            enemy->GetStageBackground(),
            true,
            120,
            true,
            0
        );
        //設置背景 相機最大可移動範圍
        float scaleFactor = context->GetWindowHeight() / m_Animation->GetScaledSize().y;
        camera->Init(player,enemy);
        camera->SetMaxOffsetX((m_Animation->GetScaledSize().x * scaleFactor - context->GetWindowWidth())/2);
        m_Animation->SetDrawData({{0, 0}, 0, {1,1}},
                    {m_Animation->GetScaledSize().x * scaleFactor, context->GetWindowHeight()},
                    0);
        //背景初始位置
        m_BGM = enemy->GetBGM();
        m_BGM->SetVolume(15);
        m_BGM->Play(-1);
        //BGM設定
        start_time = Time::GetElapsedTimeMs();

        playerController->SetState(ControllerState::Pause);
        enemyController->SetState(ControllerState::Pause);
        playerController->SetPlayerController(PlayerType::Player1);
        enemyController->SetPlayerController(PlayerType::Player2);
        player->InitPosition({-350, StageFloor},static_cast<int>(FighterDirection::Left),playerController,camera->GetMaxOffsetX());
        enemy->InitPosition({350, StageFloor},static_cast<int>(FighterDirection::Right),enemyController,camera->GetMaxOffsetX());

        player->SetEntityAdder([this](FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength) {
            this->addEntities(type, sender, strength);
        });
        enemy->SetEntityAdder([this](FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength) {
            this->addEntities(type, sender, strength);
        });

        player->SetEnemy(enemy);
        enemy->SetEnemy(player);
        bloodstick->Init(player, enemy);
    }
    void BattleScene::addEntities(FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength) {
        std::shared_ptr<FlyingObect> object=nullptr;
        switch (type) {
            case FlyingObjectType::FireBall:
                object=std::make_shared<FireBall>();
                break;
            case FlyingObjectType::Null:
                break;
        }
        if (object!=nullptr) {
            if (sender==player) {
                object->Init(sender, strength,EnemyFlyingObjects);
                PlayerFlyingObjects.push_back(object);
            }
            else {
                object->Init(sender, strength,PlayerFlyingObjects);
                EnemyFlyingObjects.push_back(object);
            }
        }
    }
    void BattleScene::UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObect>>& flyingObjects,glm::vec2 cameraOffset) {
        if (!flyingObjects.empty()) {
            std::vector<std::shared_ptr<FlyingObect>> newFlyingObjects;
            for (auto& FlyingObj : flyingObjects) {
                if (flyingObjects==PlayerFlyingObjects) {FlyingObj->Update(EnemyFlyingObjects,cameraOffset);}
                else {FlyingObj->Update(PlayerFlyingObjects,cameraOffset);}
                if (!FlyingObj->IsEnd()) {newFlyingObjects.push_back(FlyingObj);}
            }
            flyingObjects = newFlyingObjects;
        }
    }
    void BattleScene::Update(std::shared_ptr<Core::Context> context) {
        if(Time::GetElapsedTimeMs()-start_time>0) {
            playerController->SetState(ControllerState::Active);
            enemyController->SetState(ControllerState::Active);
        }
        playerController->Update(player->GetDirection(),Time::GetElapsedTimeMs());
        enemyController->Update(enemy->GetDirection(),Time::GetElapsedTimeMs());

        player->Upload(context,playerController,camera->GetCameraPos());
        enemy->Upload(context,enemyController,camera->GetCameraPos());

        bloodstick->Update();
        camera->Upload();
        UpdateFlyingObjects(PlayerFlyingObjects,camera->GetCameraPos());
        UpdateFlyingObjects(EnemyFlyingObjects,camera->GetCameraPos());

        if (Input::IsKeyDown(Keycode::RETURN)) {
            SenseEnd = true;
        }
    }
    void BattleScene::Render() {
        glm::vec2 camOffset = camera->GetCameraPos();
        m_Animation->custom_Draw(camOffset);

        player->DrawCharacter(camOffset);
        enemy->DrawCharacter(camOffset);

        bloodstick->DrawBloodstick();

        for (auto& objectGroup : std::vector{PlayerFlyingObjects, EnemyFlyingObjects}) {
            for (const auto& obj : objectGroup) {
                obj->Draw(camOffset);
            }
        }
    }
}