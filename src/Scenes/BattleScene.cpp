//
// Created by Gson on 25-3-2.
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
        m_Animation->SetDrawData({{0,0},0,{1,1}},
                    {m_Animation->GetScaledSize().x*(720/m_Animation->GetScaledSize().y),720},
                    0);
        start_time=Time::GetElapsedTimeMs();
    }

    void BattleScene::Update() {
        if (Input::IsKeyDown(Keycode::RETURN)){
            SenseEnd=true;
        }
    }

    void BattleScene::Render() {
        m_Animation->custom_Draw();
    }
}