//
// Created by Gson on 25-3-2.
//

#include "Scenes/BattleScene.hpp"

namespace Util {
    BattleScene::BattleScene() = default;

    void BattleScene::Init() {
        // 設置背景圖片
        background = std::make_shared<ImageSpace>("../sencepicture/battle/battle_bg01.png");
        background->SetFullScreen();  // 設定全螢幕
    }

    void BattleScene::Update() {
        // 這裡可以加入遊戲邏輯，例如按鍵事件
    }

    void BattleScene::Render() {
        if (background) {
            background->custom_Draw();  // 畫出背景
        }
    }
}