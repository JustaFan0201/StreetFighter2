//
// Created by Gs0n on 25-3-10.
//

#include "Others/Bloodstick.hpp"

namespace Util {
    Bloodstick::Bloodstick() {
        original = RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodBack.png";
        bloodstick_image = std::make_shared<ImageSpace>(original);
    }

    void Bloodstick::DrawBloodstick() {

        bloodstick_image->SetDrawData({{0, 260}, 0, {1, 1}}, {1200,80}, 2.0f);
        bloodstick_image->custom_Draw();
    }
}


