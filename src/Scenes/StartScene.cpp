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
        m_state=StartSceneState::Start;
    }

    void StartScene::Update(std::shared_ptr<Core::Context> context) {
        if(m_state==StartSceneState::Start) {
            if (Input::IsKeyDown(Keycode::RETURN)) {
                soundEffect->Play(0);
                m_Animation->SetDrawable(std::make_shared<Animation>(
                    std::vector<std::string>{RESOURCE_DIR"/ScenePicture/start/start_4.png"},
                    true,
                    2000,
                    false,
                    100));
                storymode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Storymodesel.png");
                battlemode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Battlemode.png");
                m_state=StartSceneState::WaitForSlect;
            }
        }
        else if(m_state==StartSceneState::WaitForSlect) {
            storymode->SetDrawData({{-180, -190}, 0, {1, 1}}, {storymode->GetScaledSize().x * 4.5, storymode->GetScaledSize().y * 4.5}, 1.0f);
            battlemode->SetDrawData({{180, -190}, 0, {1, 1}}, {battlemode->GetScaledSize().x * 4.5, battlemode->GetScaledSize().y * 4.5}, 1.0f);
            if (storymode) storymode->custom_Draw();
            if (battlemode) battlemode->custom_Draw();
            if (Input::IsKeyPressed(Keycode::A) && mode == ModeType::Battle) {
                storymode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Storymodesel.png");
                battlemode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Battlemode.png");
                soundEffect->Play(0);
                mode = ModeType::Story;
            }
            if (Input::IsKeyPressed(Keycode::D) && mode == ModeType::Story) {
                storymode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Storymode.png");
                battlemode = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/start/Battlemodesel.png");
                soundEffect->Play(0);
                mode = ModeType::Battle;
            }//選中改色
            if (Input::IsKeyDown(Keycode::RETURN)) {
                soundEffect->Play(0);
                start_time=Time::GetElapsedTimeMs();
                m_state=StartSceneState::WaitForEnd;
            }//選中音效
        }
        else if(m_state==StartSceneState::WaitForEnd) {
            if(GetPassedTime()>600) {
                SceneEnd = true;
            }
        }
    }
    void StartScene::Render() {
        if (m_Animation) {m_Animation->custom_Draw();}
        if (storymode) storymode->custom_Draw();
        if (battlemode) battlemode->custom_Draw();
    }
}
// namespace Util
