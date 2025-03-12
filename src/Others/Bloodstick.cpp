//
// Created by Gs0n on 25-3-10.
//

#include "Others/Bloodstick.hpp"

namespace Util {
    Bloodstick::Bloodstick() {
        original = "../sencepicture/Battle/others/bloodstick.png";
        bloodstick_image = std::make_shared<ImageSpace>(original);
    }

    void Bloodstick::DrawBloodstick() {

        bloodstick_image->SetDrawData({{0, 260}, 0, {1, 1}}, {1250,180}, 2.0f);
        bloodstick_image->custom_Draw();
    }
}


