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
        player->InitPosition({-350, StageFloor},static_cast<int>(FighterDirection::Left),PlayerType::Player1);
        enemy->InitPosition({350, StageFloor},static_cast<int>(FighterDirection::Right),PlayerType::Player2);

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
    void BattleScene::UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObect>>& flyingObjects) {
        if (!flyingObjects.empty()) {
            std::vector<std::shared_ptr<FlyingObect>> newFlyingObjects;
            for (auto& FlyingObj : flyingObjects) {
                if (flyingObjects==PlayerFlyingObjects) {FlyingObj->Update(EnemyFlyingObjects);}
                else {FlyingObj->Update(PlayerFlyingObjects);}
                if (!FlyingObj->IsEnd()) {newFlyingObjects.push_back(FlyingObj);}
            }
            flyingObjects = newFlyingObjects;
        }
    }
    void BattleScene::Update(std::shared_ptr<Core::Context> context) {
        camera->Upload();
        player->Upload(context);
        enemy->Upload(context);
        bloodstick->Update();
        m_Animation->SetTransform({{camera->GetCameraPos().x, 0}, 0, {1,1}});

        UpdateFlyingObjects(PlayerFlyingObjects);
        UpdateFlyingObjects(EnemyFlyingObjects);

        if (Input::IsKeyDown(Keycode::RETURN)) {
            SenseEnd = true;
        }
    }
    void BattleScene::Render() {
        m_Animation->custom_Draw();
        player->DrawCharacter();
        enemy->DrawCharacter();
        bloodstick->DrawBloodstick();
        for (auto& object : std::vector{PlayerFlyingObjects,EnemyFlyingObjects}) {
            if (!object.empty()) {
                for (const auto& FlyingObject : object) {
                    FlyingObject->Draw();
                }
            }
        }
    }
}