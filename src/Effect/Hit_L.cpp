//
// Created by asus on 2025/5/20.
//

#include "Effect/Hit_L.hpp"
namespace Util {
    Hit_L::Hit_L(): Effect("Hit_L") {
        animation=std::make_shared<AnimationSpace>(
            std::vector<std::string> {RESOURCE_DIR"/ScenePicture/Effect/"+ GetName() +"/frame (1).png"},
            false,60,true,15
        );
        AnimationInit(4,60);
    }
}