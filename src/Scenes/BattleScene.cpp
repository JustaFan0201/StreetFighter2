//
// Created by Gs0n 25-3-2.
//

#include "Scenes/BattleScene.hpp"

namespace Util {
    void BattleScene::Init(std::shared_ptr<Core::Context> context) {
        m_Animation = std::make_shared<AnimationSpace>(
            enemy->GetStageBackground(),
            true,
            60,
            true,
            0
        );
        //設置背景 相機最大可移動範圍
        float scaleFactor = context->GetWindowHeight() / m_Animation->GetScaledSize().y;
        camera->SetMaxOffsetX((m_Animation->GetScaledSize().x * scaleFactor - context->GetWindowWidth())/2);
        m_Animation->SetDrawData({{0, 0}, 0, {1,1}},
                    {m_Animation->GetScaledSize().x * scaleFactor, context->GetWindowHeight()},
                    0);
        //背景初始位置
        m_BGM = enemy->GetBGM();
        m_BGM->SetVolume(20);
        m_BGM->Play(-1);
        //BGM設定
        start_time = Time::GetElapsedTimeMs();
        player->InitPosition({-350, 0},static_cast<int>(FighterDirection::Left),StageFloor);
        enemy->InitPosition({350, 0},static_cast<int>(FighterDirection::Right),StageFloor);

    }

    void BattleScene::Update(std::shared_ptr<Core::Context> context) {
        camera->Upload();
        player->Upload(context);
        enemy->Upload(context);
        m_Animation->SetTransform({{camera->GetCameraPos().x, 0}, 0, {1,1}});

        if (Input::IsKeyDown(Keycode::RETURN)) {
            SenseEnd = true;
        }
    }
    void BattleScene::Render() {
        m_Animation->custom_Draw();
        player->DrawCharacter();
        enemy->DrawCharacter();
        bloodstick->DrawBloodstick();
    }
}