//
// Created by USER on 2025/5/2.
//
#include "FlyingObject/SonicBoom.hpp"
namespace Util {
    SonicBoom::SonicBoom(): FlyingObject("SonicBoom") {
        Type=FlyingObjectType::SonicBoom;

        FlyingObjVelocity[Keys::LP]=400;
        FlyingObjVelocity[Keys::MP]=600;
        FlyingObjVelocity[Keys::HP]=800;

        FlyingObjDmg[Keys::LP]=10;
        FlyingObjDmg[Keys::MP]=15;
        FlyingObjDmg[Keys::HP]=20;

        animations[FlyingObjectState::Start]=ActionInit(4,"Start");
        animations[FlyingObjectState::Collide]=ActionInit(3,"Collide");
        hitbox.size[FlyingObjectState::Start]={150,100};

        animationNow=std::make_shared<AnimationSpace>(
            animations[FlyingObjectState::Start],
            false,60,true,3
        );
    }
}