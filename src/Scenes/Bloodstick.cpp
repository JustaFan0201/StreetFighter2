//
// Created by Gs0n on 25-3-10.
//

#include "Scenes/Bloodstick.hpp"

#include "Scenes/Bloodstick.hpp"

namespace Util {
    Bloodstick::Bloodstick() {
        original = "../sencepicture/Battle/others/bloodstick.png";  // 血條圖片的路徑
        bloodstick_image = std::make_shared<ImageSpace>(original);  // 創建 ImageSpace 類別來顯示圖片
    }

    void Bloodstick::DrawBloodstick() {
        // 設定圖片的顯示位置和大小
        bloodstick_image->SetDrawData({{0, 260}, 0, {1, 1}}, {1263,176}, 2.0f);  // 這裡的 {300, 50} 代表血條的大小
        bloodstick_image->custom_Draw();  // 繪製圖片
    }
}


