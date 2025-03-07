//
// Created by Gson 25-3-2.
//

#include "Scenes/BattleScene.hpp"

namespace Util {
    void BattleScene::Init() {
        m_Animation = std::make_shared<AnimationSpace>(
            enemy->GetStageBackground(),
            true,
            250,
            true,
            0
        );
        //設置背景
        float scaleFactor = 720.0f / m_Animation->GetScaledSize().y;
        camera->SetMaxOffsetX(m_Animation->GetScaledSize().x * scaleFactor / 2 - 640);
        //設定相機最大可移動範圍
        m_Animation->SetDrawData({{0, 0}, 0, {1,1}},
                    {m_Animation->GetScaledSize().x * scaleFactor, 720},
                    0);
        //背景初始位置
        m_BGM = enemy->GetBGM();
        m_BGM->SetVolume(25);
        m_BGM->Play(-1);
        //BGM設定
        start_time = Time::GetElapsedTimeMs();
    }

    void BattleScene::Update() {
        camera->Upload();
        player->Upload();
        m_Animation->SetDrawData({{-camera->GetCameraPos().x, 0}, 0, {1,1}},
                    {m_Animation->GetScaledSize().x * (720.0f / m_Animation->GetScaledSize().y), 720},
                    0);

        if (Input::IsKeyDown(Keycode::RETURN)) {
            SenseEnd = true;
        }
    }
    void BattleScene::Render() {
        m_Animation->custom_Draw();
        player->DrawCharacter();
    }
}