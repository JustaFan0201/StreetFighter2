//
// Created by asus on 2025/5/21.
//

#include "Effect/Block_M.hpp"
namespace Util {
    Block_M::Block_M(): Effect("Block_M") {
        animation=std::make_shared<AnimationSpace>(
            std::vector<std::string> {RESOURCE_DIR"/ScenePicture/Effect/"+ GetName() +"/frame (1).png"},
            false,60,true,15
        );
        AnimationInit(4,60);
    }
}