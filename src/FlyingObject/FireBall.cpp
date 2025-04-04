//
// Created by FanFan on 2025/4/5.
//

#include "FlyingObject/FireBall.hpp"
namespace Util {
    FireBall::FireBall(): FlyingObect("FireBall") {
        Type=FlyingObjectType::FireBall;

        FireBallVelocity[Keys::LP]=450;
        FireBallVelocity[Keys::MP]=660;
        FireBallVelocity[Keys::HP]=900;

        animations[FlyingObjectState::Start]=ActionInit(2,"Start");
        animations[FlyingObjectState::Collide]=ActionInit(2,"Collide");
        frames[FlyingObjectState::Start]={60,60};
        frames[FlyingObjectState::Collide]={120, 180, 120};
        offset[FlyingObjectState::Start]={{0,0},{0,0}};
        offset[FlyingObjectState::Collide]={{0,0},{0,0},{0,0}};

        hitbox.offset[FlyingObjectState::Start]={{0,0},{0,0}};
        hitbox.size[FlyingObjectState::Start]={100,100};

        animationNow=std::make_shared<AnimationSpace>(
            animations[FlyingObjectState::Start],
            true,200,true,3
        );
    }

    void FireBall::Init(std::shared_ptr<Fighter> fighter,Keys Strength) {
        this->fighter=fighter;
        direction=fighter->GetDirection();
        velocity.x=FireBallVelocity[Strength];

        animationNow->SetDrawData({(fighter->GetCurrentOffsetPosition()+glm::vec2 {150*direction,40}),
            0,{direction,1}},
            animationNow->GetOriginalSize()*glm::vec2{3,3},3);
        ChangeState(FlyingObjectState::Start);
    }
    void FireBall::Update() {
        Movement();
        if(currentState==FlyingObjectState::Start) {
            if (IsAnimationEnd()) {
                SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
            }
        }
        else if(currentState==FlyingObjectState::Collide) {
            if (IsAnimationEnd()) {
                ObjectIsEnd=true;
            }
        }
    }
    void FireBall::Draw() {
        animationNow->custom_Draw();
    }
}
