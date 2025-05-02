//
// Created by FanFan on 2025/4/5.
//

#include "FlyingObject/FireBall.hpp"
namespace Util {
    FireBall::FireBall(): FlyingObject("FireBall") {
        Type=FlyingObjectType::FireBall;

        FlyingObjVelocity[Keys::LP]=450;
        FlyingObjVelocity[Keys::MP]=650;
        FlyingObjVelocity[Keys::HP]=750;

        FlyingObjDmg[Keys::LP]=10;
        FlyingObjDmg[Keys::MP]=15;
        FlyingObjDmg[Keys::HP]=20;

        animations[FlyingObjectState::Start]=ActionInit(2,"Start");
        animations[FlyingObjectState::Collide]=ActionInit(3,"Collide");
        hitbox.size[FlyingObjectState::Start]={150,150};

        animationNow=std::make_shared<AnimationSpace>(
            animations[FlyingObjectState::Start],
            true,120,true,3
        );
    }
}
