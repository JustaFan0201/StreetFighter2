//
// Created by FanFan on 2025/4/5.
//

#include "FlyingObject/FlyingObject.hpp"
namespace Util {
    std::vector<std::string> FlyingObect::ActionInit(int picture_number, std::string Action) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/FlyingObject/"+ GetName() +"/"+ Action +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        return Allframe;
    }
    void FlyingObect::SetAnimation(FlyingObjectState action, int duration) {
        if (animations.find(action) != animations.end()) {
            animationNow->SetDrawable(std::make_shared<Animation>(animations[action], true, duration, false));
        }
    }
    void FlyingObect::ChangeState(FlyingObjectState newState) {
        if (currentState != newState) {
            currentState = newState;
            SetAnimation(currentState,60);
        }
    }

    void FlyingObect::Movement() {
        glm::vec2 position={animationNow->GetTransform().translation.x+direction*velocity.x*Time::GetDeltaTimeMs()/1000,
            animationNow->GetTransform().translation.y};
        if (position.x<-640 || position.x>640) {
            ObjectIsEnd=true;
        }
        animationNow->SetDrawData(
            {position, 0, {direction, 1}},
            animationNow->GetOriginalSize()*glm::vec2 {3,3},
            3.0f
        );
        if (IsCollidedEnemy()==FlyingObjectCollidedState::Enemy) {
            if(enemy->IsBlocking()) {
                enemy->AttackBlock();
            }
            else {
                fighter->AttackHit(HitStrength::H,HitLocation::Head,FireBallDmg[Strength]);
            }
            ChangeState(FlyingObjectState::Collide);
        }
        if (IsCollidedEntity()==FlyingObjectCollidedState::FlyingObject) {
            ChangeState(FlyingObjectState::Collide);
        }
    }
    FlyingObjectCollidedState FlyingObect::IsCollidedEnemy() {
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
                return FlyingObjectCollidedState::Enemy;}
        }
        return FlyingObjectCollidedState::Null;
    }
    FlyingObjectCollidedState FlyingObect::IsCollidedEntity() {
        for (auto EnemyEntity : EnemyFlyingObjects) {
            auto EnemyEntityPos = EnemyEntity->GetCurrentPosition();
            auto EnemyEntitySize = EnemyEntity->GetCurrentHitbox();

            if(RectangleOverlap(
                GetCurrentPosition(),
                GetCurrentHitbox(),
                EnemyEntityPos,
                EnemyEntitySize)){
                return FlyingObjectCollidedState::FlyingObject;
            }
        }
        return FlyingObjectCollidedState::Null;
    }
    void FlyingObect::Update(std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects) {
        this->EnemyFlyingObjects=EnemyFlyingObjects;
        if(currentState==FlyingObjectState::Start) {
            Movement();
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
    void FlyingObect::Draw() {
        animationNow->custom_Draw();
    }
}

