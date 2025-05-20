//
// Created by asus on 2025/5/21.
//

#include "Effect/Block_H.hpp"
namespace Util {
    Block_H::Block_H(): Effect("Block_H") {
        animation=std::make_shared<AnimationSpace>(
            std::vector<std::string> {RESOURCE_DIR"/ScenePicture/Effect/"+ GetName() +"/frame (1).png"},
            false,60,true,15
        );
        AnimationInit(4,60);
    }
}