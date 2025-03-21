// StartScene.cpp

#include "Scenes/StartScene.hpp"

namespace Util {
    StartScene::StartScene() = default;

    void StartScene::Init(std::shared_ptr<Core::Context> context) {
        m_Animation = std::make_shared<AnimationSpace>(
            std::vector<std::string> {
                RESOURCE_DIR"/ScenePicture/start/start_1.png",
                RESOURCE_DIR"/ScenePicture/start/start_2.png",
                RESOURCE_DIR"/ScenePicture/start/start_3.png"
            },
            true,
            2000,
            false,
            0
        );
        //開場動畫
        m_BGM = std::make_shared<BGM>(RESOURCE_DIR"/music/title.mp3");
        m_BGM->SetVolume(15);
        m_BGM->Play(-1);
        soundEffect->SetVolume(30);
        //開場音樂
        m_Animation->SetSize({context->GetWindowWidth(),context->GetWindowHeight()});
    }

    void StartScene::Update(std::shared_ptr<Core::Context> context) {
        if (Time::GetElapsedTimeMs() - start_time > 4000) {
            if (m_WaitingForEnter) {
                if (Input::IsKeyDown(Keycode::RETURN)) {
                    m_WaitingForEnter = false;
                    Word_1->SetDrawData({{-180, -180},0,{1,1}},Word_1->GetDrawable()->GetSize(),1.0f);
                    Word_2->SetDrawData({{180, -180},0,{1,1}},Word_1->GetDrawable()->GetSize(),1.0f);

                    soundEffect->Play(0);

                    m_Animation->SetDrawable(std::make_shared<Animation>(
                        std::vector<std::string>{RESOURCE_DIR"/ScenePicture/start/start_4.png"},
                        true,
                        2000,
                        false,
                        100));
                }
            }//選模式(Story and Battle)
            else {
                if (Word_1) Word_1->custom_Draw();
                if (Word_2) Word_2->custom_Draw();
                if (Input::IsKeyPressed(Keycode::A) && mode == 1) {
                    Word_1->SetColor(Color(255, 127, 80));
                    Word_2->SetColor(Color(255, 255, 255));
                    soundEffect->Play(0);
                    mode = 0;
                }
                if (Input::IsKeyPressed(Keycode::D) && mode == 0) {
                    Word_2->SetColor(Color(255, 127, 80));
                    Word_1->SetColor(Color(255, 255, 255));
                    soundEffect->Play(0);
                    mode = 1;
                }//選中改色
                if (Input::IsKeyDown(Keycode::RETURN)) {
                    soundEffect->Play(0);
                    SDL_Delay(600);
                    SenseEnd = true;
                }//選中音效
            }
        }
    }

    void StartScene::Render() {
        if (m_Animation) {
            m_Animation->custom_Draw();
        }
    }
}
// namespace Util
