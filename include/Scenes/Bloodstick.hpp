//
// Created by Gs0n on 25-3-10.
//

#ifndef BLOODSTICK_HPP
#define BLOODSTICK_HPP

#include <memory>
#include <string>
#include "AnimationSpace.hpp"  // 假設這是你處理動畫的類別
#include "Scene.hpp"


namespace Util {
    class Bloodstick {
    private:
        std::string original;  // 血條圖片的路徑
        std::shared_ptr<ImageSpace> bloodstick_image;  // 用於顯示血條圖片的對象

    public:
        Bloodstick();
        void DrawBloodstick();  // 用來繪製血條
    };
}

#endif //BLOODSTICK_HPP


