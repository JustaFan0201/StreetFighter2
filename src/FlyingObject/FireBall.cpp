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

        FireBallDmg[Keys::LP]=10;
        FireBallDmg[Keys::MP]=20;
        FireBallDmg[Keys::HP]=30;

        animations[FlyingObjectState::Start]=ActionInit(2,"Start");
        animations[FlyingObjectState::Collide]=ActionInit(3,"Collide");
        hitbox.size[FlyingObjectState::Start]={100,100};

        animationNow=std::make_shared<AnimationSpace>(
            animations[FlyingObjectState::Start],
            true,120,true,3
        );
    }

    void FireBall::Init(std::shared_ptr<Fighter> fighter,Keys Strength,std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects) {
        this->EnemyFlyingObjects=EnemyFlyingObjects;
        this->fighter=fighter;
        enemy=fighter->GetEnemy();
        direction=fighter->GetNewDirection();
        velocity.x=FireBallVelocity[Strength];
        this->Strength=Strength;

        animationNow->SetDrawData({(fighter->GetCurrentOffsetPosition()+glm::vec2 {150*direction,40}),
            0,{direction,1}},
            animationNow->GetOriginalSize()*glm::vec2{3,3},3);
        ChangeState(FlyingObjectState::Start);
    }
}
