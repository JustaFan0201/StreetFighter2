//
// Created by USER on 2025/5/2.
//
#include "FlyingObject/SonicBoom.hpp"
namespace Util {
    SonicBoom::SonicBoom(): FlyingObject("SonicBoom") {
        FlyingObjVelocity[Keys::LP]=450;
        FlyingObjVelocity[Keys::MP]=550;
        FlyingObjVelocity[Keys::HP]=650;

        FlyingObjDmg[Keys::LP]=10;
        FlyingObjDmg[Keys::MP]=15;
        FlyingObjDmg[Keys::HP]=20;

        animations[FlyingObjectState::Start]=ActionInit(4,"Start");
        animations[FlyingObjectState::Collide]=ActionInit(3,"Collide");
        hitbox.size[FlyingObjectState::Start]={135,100};

        animationNow=std::make_shared<AnimationSpace>(
            animations[FlyingObjectState::Start],
            false,60,true,3
        );
    }
}