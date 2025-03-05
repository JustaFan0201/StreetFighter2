//
// Created by Gson 25-3-2.
//


#include "Scenes/BattleScene.hpp"

namespace Util {
    void BattleScene::Init() {
        // 設置背景圖片
        m_Animation = std::make_shared<AnimationSpace>(
            enemy->GetStageBackground(),
            true,
            250,
            true,
            0
        );

        maxOffsetX = m_Animation->GetScaledSize().x * (720 / m_Animation->GetScaledSize().y);

        cameraPos.x = maxOffsetX / 2 - 940;

        // 拉伸背景圖片，確保高度為 720，寬度按比例擴展
        m_Animation->SetDrawData({{0,0},0,{1,1}},
                    {maxOffsetX, 720},
                    0);

        start_time = Time::GetElapsedTimeMs();
    }

    void BattleScene::Update() {
        int moveSpeed = 10;

        if (Input::IsKeyDown(Keycode::A)) {
            cameraPos.x -= moveSpeed;
        }
        else if (Input::IsKeyDown(Keycode::D)) {
            cameraPos.x += moveSpeed;
        }

        if (cameraPos.x < 0) cameraPos.x = 0;
        if (cameraPos.x + 1880 > maxOffsetX) cameraPos.x = maxOffsetX - 1880;
        // !!!!!!!!寬是1880!!!!!!!!


        m_Animation->SetDrawData({{-cameraPos.x, 0}, 0, {1,1}},
                    {maxOffsetX, 720},
                    0);

        if (Input::IsKeyDown(Keycode::RETURN)){
            SenseEnd = true;
        }
    }

    void BattleScene::Render() {
        m_Animation->custom_Draw();
    }
}
