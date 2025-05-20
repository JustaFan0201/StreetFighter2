//
// Created by asus on 2025/5/14.
//

#include "FlyingObject/YogaFire.hpp"
namespace Util {
    YogaFire::YogaFire(): FlyingObject("YogaFire") {
        FlyingObjVelocity[Keys::LP]=300;
        FlyingObjVelocity[Keys::MP]=400;
        FlyingObjVelocity[Keys::HP]=500;

        FlyingObjDmg[Keys::LP]=12;
        FlyingObjDmg[Keys::MP]=17;
        FlyingObjDmg[Keys::HP]=22;

        animations[FlyingObjectState::Start]=ActionInit(8,"Start");
        animations[FlyingObjectState::Collide]=ActionInit(3,"Collide");
        hitbox.size[FlyingObjectState::Start]={135,100};

        animationNow=std::make_shared<AnimationSpace>(
            animations[FlyingObjectState::Start],
            false,60,true,3
        );
    }
}