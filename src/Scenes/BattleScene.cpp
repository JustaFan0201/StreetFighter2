//
// Created by Gson 25-3-2.
//

#include "Scenes/BattleScene.hpp"

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

        maxOffsetX = m_Animation->GetScaledSize().x * (720 / m_Animation->GetScaledSize().y)/2- 640;
        cameraPos.x = 0;
        m_Animation->SetDrawData({{0,0},0,{1,1}},
                    {m_Animation->GetScaledSize().x * (720 / m_Animation->GetScaledSize().y), 720},
                    0);
        start_time = Time::GetElapsedTimeMs();
    }

    void BattleScene::Update() {
        int moveSpeed = 10;
        if (Input::IsKeyPressed(Keycode::A)) {
            cameraPos.x -= moveSpeed;
        }
        else if (Input::IsKeyPressed(Keycode::D)) {
            cameraPos.x += moveSpeed;
        }
        if (cameraPos.x < -maxOffsetX ) cameraPos.x = -maxOffsetX ;
        if (cameraPos.x >  maxOffsetX ) cameraPos.x = maxOffsetX ;

        m_Animation->SetDrawData({{-cameraPos.x, 0}, 0, {1,1}},
                    {m_Animation->GetScaledSize().x * (720 / m_Animation->GetScaledSize().y), 720},
                    0);

        if (Input::IsKeyDown(Keycode::RETURN)){
            SenseEnd = true;
        }
    }

    void BattleScene::Render() {
        m_Animation->custom_Draw();
    }
}
