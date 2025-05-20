//
// Created by asus on 2025/5/20.
//

#include "Effect/Effect.hpp"
namespace Util {
    void Effect::AnimationInit(int picture_number, int duration) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/Effect/"+ GetName() +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        animation->SetDrawable(std::make_shared<Animation>(Allframe, true, duration, false));
    }
    void Effect::Init(glm::vec2 position) {
        animation->SetDrawData({position,0,{1,1}},
            animation->GetOriginalSize()*glm::vec2{5,5},15);
    }
    void Effect::Update() {
        if(IsAnimationEnd()) {
            EffectIsEnd = true;
        }
    }
    void Effect::Draw(glm::vec2 cameraPos) {
        animation->custom_Draw(cameraPos);
    }
}

