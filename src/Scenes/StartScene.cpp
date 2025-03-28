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
                    soundEffect->Play(0);
                    m_Animation->SetDrawable(std::make_shared<Animation>(
                        std::vector<std::string>{RESOURCE_DIR"/ScenePicture/start/start_4.png"},
                        true,
                        2000,
                        false,
                        100));
                    storymode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Storymodesel.png");
                    battlemode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Battlemode.png");
                }
            }//選模式(Story and Battle)
            else {
                storymode->SetDrawData({{-180, -190}, 0, {1, 1}}, {storymode->GetScaledSize().x * 4.5, storymode->GetScaledSize().y * 4.5}, 1.0f);
                battlemode->SetDrawData({{180, -190}, 0, {1, 1}}, {battlemode->GetScaledSize().x * 4.5, battlemode->GetScaledSize().y * 4.5}, 1.0f);

                if (storymode) storymode->custom_Draw();
                if (battlemode) battlemode->custom_Draw();
                if (Input::IsKeyPressed(Keycode::A) && mode == 1) {
                    storymode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Storymodesel.png");
                    battlemode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Battlemode.png");
                    soundEffect->Play(0);
                    mode = 0;
                }
                if (Input::IsKeyPressed(Keycode::D) && mode == 0) {
                    storymode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Storymode.png");
                    battlemode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Battlemodesel.png");
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
