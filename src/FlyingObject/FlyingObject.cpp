//
// Created by FanFan on 2025/4/5.
//

#include "FlyingObject/FlyingObject.hpp"
namespace Util {
    std::vector<std::string> FlyingObject::ActionInit(int picture_number, std::string Action) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/FlyingObject/"+ GetName() +"/"+ Action +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        return Allframe;
    }
    void FlyingObject::SetAnimation(FlyingObjectState action, int duration) {
        if (animations.find(action) != animations.end()) {
            animationNow->SetDrawable(std::make_shared<Animation>(animations[action], true, duration, false));
        }
    }
    void FlyingObject::ChangeState(FlyingObjectState newState) {
        if (currentState != newState) {
            currentState = newState;
            SetAnimation(currentState,60);
        }
    }

    void FlyingObject::Movement(glm::vec2 cameraOffset) {
        glm::vec2 position={animationNow->GetTransform().translation.x+direction*velocity.x*Time::GetDeltaTimeMs()/1000,
            animationNow->GetTransform().translation.y};
        if (position.x-cameraOffset.x<-640 || position.x-cameraOffset.x>640) {
            ObjectIsEnd=true;
        }
        animationNow->SetDrawData(
            {position, 0, {direction, 1}},
            animationNow->GetOriginalSize()*glm::vec2 {3,3},
            3.0f
        );
        if (IsCollidedEnemy()==FlyingObjectCollidedState::Enemy) {
            ChangeState(FlyingObjectState::Collide);
        }
        if (IsCollidedEntity()==FlyingObjectCollidedState::FlyingObject) {
            ChangeState(FlyingObjectState::Collide);
        }
    }
    FlyingObjectCollidedState FlyingObject::IsCollidedEnemy() {
        if(currentState!=FlyingObjectState::Start){return FlyingObjectCollidedState::Null;}
        auto enemyPos = enemy->GetCurrentOffsetPosition();
        auto bodyOffsets = enemy->GetCurrentHurtboxOffset();
        auto bodySizes = enemy->GetCurrentHurtboxSize();

        for (size_t i = 0; i < bodyOffsets.size(); i++) {
            auto& BodyOffset = bodyOffsets[i];
            auto& BodySize = bodySizes[i];
            if(RectangleOverlap(
                GetCurrentPosition(),
                GetCurrentHitbox(),
                enemyPos+BodyOffset,
                BodySize)){
                glm::vec2 EffectPos=enemyPos+BodyOffset-glm::vec2{12,12}+glm::vec2{GetRandomNum(0,24),GetRandomNum(0,24)};
                if(!enemy->GetSpecificState().InvincibleForFlyObj.count(enemy->GetCurrentState())&&
                    !enemy->GetSpecificState().Invincible.count(enemy->GetCurrentState())) {
                    if(enemy->IsBlocking()) {
                        enemy->AddEffect(HitStrength::H,BeHitType::Block,EffectPos);
                        enemy->GetAttack(FlyingObjDmg[Strength]/5);
                        enemy->AttackBlock();
                    }
                    else {
                        enemy->AddEffect(HitStrength::H,BeHitType::Hit,EffectPos);
                        fighter->AttackHit(HitStrength::H,HitLocation::Head,FlyingObjDmg[Strength]);
                        enemy->GetSFX()[enemy->GetCurrentState()]->Play();
                    }
                    return FlyingObjectCollidedState::Enemy;
                }
            }
        }
        return FlyingObjectCollidedState::Null;
    }
    FlyingObjectCollidedState FlyingObject::IsCollidedEntity() {
        if(currentState!=FlyingObjectState::Start){return FlyingObjectCollidedState::Null;}
        for (auto EnemyEntity : EnemyFlyingObjects) {
            auto EnemyEntityPos = EnemyEntity->GetCurrentPosition();
            auto EnemyEntitySize = EnemyEntity->GetCurrentHitbox();
            if(EnemyEntity->currentState!=FlyingObjectState::Collide) {
                if(RectangleOverlap(
                    GetCurrentPosition(),
                    GetCurrentHitbox(),
                    EnemyEntityPos,
                    EnemyEntitySize)){
                    EnemyEntity->ChangeState(FlyingObjectState::Collide);
                    return FlyingObjectCollidedState::FlyingObject;
                }
            }
        }
        return FlyingObjectCollidedState::Null;
    }
    void FlyingObject::Init(std::shared_ptr<Fighter> fighter,Keys Strength,std::vector<std::shared_ptr<FlyingObject>> EnemyFlyingObjects) {
        this->EnemyFlyingObjects=EnemyFlyingObjects;
        this->fighter=fighter;
        enemy=fighter->GetEnemy();
            direction=fighter->GetDirection();
        velocity.x=FlyingObjVelocity[Strength];
        this->Strength=Strength;
        ChangeState(FlyingObjectState::Start);
        animationNow->SetDrawData({(fighter->GetCurrentOffsetPosition()+glm::vec2 {150*direction,40}),
            0,{direction,1}},
            animationNow->GetOriginalSize()*glm::vec2{3,3},3);
    }
    void FlyingObject::Update(std::vector<std::shared_ptr<FlyingObject>> EnemyFlyingObjects,glm::vec2 cameraOffset) {
        this->EnemyFlyingObjects=EnemyFlyingObjects;
        if(currentState==FlyingObjectState::Start) {
            Movement(cameraOffset);
            if (IsAnimationEnd()) {
                SetAnimation(currentState,120);
            }
        }
        else if(currentState==FlyingObjectState::Collide) {
            if (IsAnimationEnd()) {
                ObjectIsEnd=true;
            }
        }
    }
    void FlyingObject::Draw(glm::vec2 cameraOffset) {
        animationNow->custom_Draw(cameraOffset);
    }
}

