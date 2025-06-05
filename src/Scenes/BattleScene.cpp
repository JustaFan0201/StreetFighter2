//
// Created by Gs0n 25-3-2.
//

#include "Scenes/BattleScene.hpp"

#include "../../PTSD/lib/sdl2/src/joystick/windows/SDL_windowsjoystick_c.h"

namespace Util {
    void BattleScene::Init(std::shared_ptr<Core::Context> context) {
        m_Animation = std::make_shared<AnimationSpace>(
            enemy->GetStageBackground(),
            true,
            120,
            true,
            0
        );
        m_BGM = enemy->GetBGM();
        m_BGM->SetVolume(15);
        m_BGM->Play(-1);
        //BGM設定
        round=1;
        PlayerWinCounter=0;
        EnemyWinCounter=0;
        ui->JudgeWinCount(PlayerWinCounter,EnemyWinCounter);
        RoundStart(context);
    }
    void BattleScene::InitControllerSetting() {
        playerController->SetState(ControllerState::Pause);
        enemyController->SetState(ControllerState::Pause);
        playerController->SetPlayerController(PlayerType::Player1);
        if (mode==ModeType::Story){enemyController->SetPlayerController(PlayerType::Ai);}
        else{enemyController->SetPlayerController(PlayerType::Player2);}

        playerController->SetAiSpecials(static_cast<int>(player->GetSpecificState().SpecialStates.size()));
        enemyController->SetAiSpecials(static_cast<int>(enemy->GetSpecificState().SpecialStates.size()));
    }
    void BattleScene::InitPlayerSetting() {
        player->InitPosition({-350, StageFloor },static_cast<int>(FighterDirection::Left),playerController,camera->GetMaxOffsetX());
        enemy->InitPosition({350, StageFloor},static_cast<int>(FighterDirection::Right),enemyController,camera->GetMaxOffsetX());

        player->SetEntityAdder([this](FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength) {
            this->addEntities(type, sender, strength);
        });
        enemy->SetEntityAdder([this](FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength) {
            this->addEntities(type, sender, strength);
        });
        player->SetEffectAdder([this](HitStrength strength,BeHitType behittype, glm::vec2 position) {
            this->addEffects(strength, behittype, position);
        });
        enemy->SetEffectAdder([this](HitStrength strength,BeHitType behittype, glm::vec2 position) {
            this->addEffects(strength, behittype, position);
        });
        player->SetEnemy(enemy);
        enemy->SetEnemy(player);
    }
    void BattleScene::RoundStart(std::shared_ptr<Core::Context> context) {
        defeatedType=DefeatedType::Null;
        lossType=LossType::Null;
        float scaleFactor = context->GetWindowHeight() / m_Animation->GetScaledSize().y;
        camera->Init(player,enemy);
        camera->SetMaxOffsetX((m_Animation->GetScaledSize().x * scaleFactor - context->GetWindowWidth())/2);
        m_Animation->SetDrawData({{0, 0}, 0, {1,1}},
                    {m_Animation->GetScaledSize().x * scaleFactor, context->GetWindowHeight()},
                    0);
        //背景初始位置
        start_time = Time::GetElapsedTimeMs();
        InitControllerSetting();
        InitPlayerSetting();
        ui->Init(player, enemy);
    }
    void BattleScene::addEntities(FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength) {
        std::shared_ptr<FlyingObject> object= flyingObjFactory[type]();
        if (object) {
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
    void BattleScene::UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObject>>& flyingObjects,glm::vec2 cameraOffset) {
        if (!flyingObjects.empty()) {
            std::vector<std::shared_ptr<FlyingObject>> newFlyingObjects;
            for (auto& FlyingObj : flyingObjects) {
                if (flyingObjects==PlayerFlyingObjects) {FlyingObj->Update(EnemyFlyingObjects,cameraOffset);}
                else if (flyingObjects==EnemyFlyingObjects) {FlyingObj->Update(PlayerFlyingObjects,cameraOffset);}
                if (!FlyingObj->IsEnd()) {newFlyingObjects.push_back(FlyingObj);}
            }
            flyingObjects = newFlyingObjects;
        }
    }
    void BattleScene::addEffects(HitStrength strength,BeHitType behittype, glm::vec2 position) {
        HitStrength newStr = strength;
        std::shared_ptr<Effect> effect;
        if(strength==HitStrength::SP) {
            newStr=HitStrength::H;
        }
        switch (behittype) {
            case BeHitType::Hit:
                effect= HitEffectFactory[newStr]();
            break;
            case BeHitType::Block:
                effect= BlockEffectFactory[newStr]();
            break;
            default:
                return;
        }
        effect->Init(position);
        Effects.push_back(effect);
    }
    void BattleScene::UpdateEffects() {
        if (!Effects.empty()) {
            std::vector<std::shared_ptr<Effect>> newEffects;
            for (auto& effect :Effects) {
                effect->Update();
                if(!effect->IsEnd()) {newEffects.push_back(effect);}
            }
            Effects = newEffects;
        }
    }
    void BattleScene::LetSomeoneLoss() const {
        if(Input::IsKeyPressed(Keycode::LSHIFT)) {
            if(Input::IsKeyDown(Keycode::NUM_9)) {
                player->SetHP(0);
            }
            if(Input::IsKeyDown(Keycode::NUM_0)) {
                enemy->SetHP(0);
            }
        }
    }
    void BattleScene::Update(std::shared_ptr<Core::Context> context) {
        ControllerState();
        if(!ui->GetRoundStartIsEnd()) {ui->RoundStart(round);}
        else{ui->Update();}

        playerController->Update(player->GetDirection(),Time::GetElapsedTimeMs());
        enemyController->Update(enemy->GetDirection(),Time::GetElapsedTimeMs());

        player->Update(context,playerController,camera->GetCameraPos());
        enemy->Update(context,enemyController,camera->GetCameraPos());

        camera->Update(context->GetWindowWidth()/2);
        UpdateFlyingObjects(PlayerFlyingObjects,camera->GetCameraPos());
        UpdateFlyingObjects(EnemyFlyingObjects,camera->GetCameraPos());
        UpdateEffects();

        switch (ui->GetState()) {
            case State::WaitForEnd:case State::TimeOver:
                LossJudge();
                break;
            case State::EndEventLoss:
                LossStateForFighter();
                break;
            case State::EndEventWin:
                WinStateForFighter();
                break;
            case State::End:
                EndForRound(context);
                break;
            default:
                break;
        }
        //debug
        LetSomeoneLoss();
    }
    void BattleScene::ControllerState() {
        if(ui->GetState()==State::WaitForEnd) {
            playerController->SetState(ControllerState::Active);
            enemyController->SetState(ControllerState::Active);
        }
        else {
            playerController->SetState(ControllerState::Pause);
            enemyController->SetState(ControllerState::Pause);
        }
    }
    void BattleScene::LossJudge() {
        if(ui->GetState()==State::TimeOver) {
            lossType=LossType::TimeOver;
            if(player->GetHP()==enemy->GetHP()){defeatedType=DefeatedType::Both;}
            else if(player->GetHP()<enemy->GetHP()){defeatedType=DefeatedType::Player;}
            else {defeatedType=DefeatedType::Enemy;}
            ui->ChangeState(State::EndEventLoss);
        }
        else if(player->GetHP()<=0||enemy->GetHP()<=0) {
            lossType=LossType::NoHP;
            if (player->GetHP()<=0&&enemy->GetHP()<=0) {defeatedType=DefeatedType::Both;}
            else if(player->GetHP()<=0) {defeatedType=DefeatedType::Player;}
            else if(enemy->GetHP()<=0) {defeatedType=DefeatedType::Enemy;}
            ui->ChangeState(State::EndEventLoss);
        }
    }
    void BattleScene::LossStateForFighter(){
        if(lossType==LossType::NoHP) {
            switch (defeatedType) {
                case DefeatedType::Both:
                    player->ChangeState(FighterState::DefeatedLoss);
                    enemy->ChangeState(FighterState::DefeatedLoss);
                    break;
                case DefeatedType::Player:
                    player->ChangeState(FighterState::DefeatedLoss);
                    break;
                case DefeatedType::Enemy:
                    enemy->ChangeState(FighterState::DefeatedLoss);
                    break;
                default:
                    break;
            }
        }
        start_time = Time::GetElapsedTimeMs();
        ui->ChangeState(State::EndEventWin);
    }
    void BattleScene::WinStateForFighter() {
        if(GetPassedTime()>=2000) {
            if(lossType==LossType::TimeOver) {
                switch (defeatedType) {
                    case DefeatedType::Both:
                        player->ChangeState(FighterState::TimeOverLoss);
                        enemy->ChangeState(FighterState::TimeOverLoss);
                    break;
                    case DefeatedType::Player:
                        player->ChangeState(FighterState::TimeOverLoss);
                    break;
                    case DefeatedType::Enemy:
                        enemy->ChangeState(FighterState::TimeOverLoss);
                    break;
                    default:
                        break;;
                }
            }
            switch (defeatedType) {
                case DefeatedType::Both:
                    PlayerWinCounter++;
                    EnemyWinCounter++;
                break;
                case DefeatedType::Player:
                    enemy->ChangeState(FighterState::WinStart);
                    EnemyWinCounter++;
                break;
                case DefeatedType::Enemy:
                    player->ChangeState(FighterState::WinStart);
                    PlayerWinCounter++;
                break;
                default:
                    break;
            }
            start_time = Time::GetElapsedTimeMs();
            ui->JudgeWinCount(PlayerWinCounter,EnemyWinCounter);
            ui->ChangeState(State::End);
        }
    }
    void BattleScene::EndForRound(std::shared_ptr<Core::Context> context) {
        if(GetPassedTime()>=3000) {
            switch (defeatedType) {
                case DefeatedType::Both:
                break;
                case DefeatedType::Player:
                break;
                case DefeatedType::Enemy:
                break;
                default:
                    break;;
            }
            JudgeBattleEnd();
            round++;
            RoundStart(context);
        }
    }
    void BattleScene::JudgeBattleEnd() {
        //std::cout<<PlayerWinCounter<<"JudgeBattleEnd"<<EnemyWinCounter<<std::endl;
        if(PlayerWinCounter==2&&EnemyWinCounter==2) {
            finalresult=FinalResult::Tie;
            SceneEnd= true;
        }
        else if(PlayerWinCounter==2) {
            finalresult=FinalResult::Player1Win;
            SceneEnd= true;
        }
        else if(EnemyWinCounter==2) {
            finalresult=FinalResult::Player2Win;
            SceneEnd= true;
        }
    }
    void BattleScene::Render() {
        glm::vec2 camOffset = camera->GetCameraPos();
        m_Animation->custom_Draw(camOffset);

        player->DrawCharacter(camOffset);
        enemy->DrawCharacter(camOffset);

        ui->DrawUI();
        for (auto& objectGroup : std::vector{PlayerFlyingObjects, EnemyFlyingObjects}) {
            for (const auto& obj : objectGroup) {
                obj->Draw(camOffset);
            }
        }
        for (auto& effect : Effects) {
            effect->Draw(camOffset);
        }
    }
}
