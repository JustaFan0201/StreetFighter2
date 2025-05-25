//
// Created by asus on 2025/5/24.
//

#include "Scenes/ContinueScene.hpp"
namespace Util {
    void ContinueScene::Init(std::shared_ptr<Core::Context> context) {
        start_time=Time::GetElapsedTimeMs();
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/14 Continue....mp3");
        m_BGM->Play();
        countsound = std::make_shared<SFX>(RESOURCE_DIR"/voice/06 Other/9.wav");
        countsound->Play();
        continuesound=std::make_shared<SFX>(RESOURCE_DIR"/voice/01 Select Screen & World Map/SFII_03 - Selection.wav");
        gameoversound=std::make_shared<SFX>(RESOURCE_DIR"/music/15 Game Over!.mp3");
        player_face=std::make_shared<ImageSpace>(player->GetLossFace());

        player_face->SetDrawData({{-280, 50},0,{1,1}},
                {300,player_face->GetScaledSize().y*300/player_face->GetScaledSize().x},
                2.0f);
        time_picture=std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/ContinueScene/9.png");
        gameover_picture=std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/ContinueScene/GameOver.png");
        gameover_picture->SetDrawData({{0, 0},0,{1,1}},
                gameover_picture->GetScaledSize()*glm::vec2{5,5},
                10.0f);
        gameover_picture->SetVisible(false);
        currentstate=ContinueSceneState::Start;
    }
    void ContinueScene::Update(std::shared_ptr<Core::Context> context){
        if(currentstate==ContinueSceneState::Start) {
            if(timer!=(9 - static_cast<int>(GetPassedTime()) / 1000 ) % 10) {
                timer = (9 - static_cast<int>(GetPassedTime()) / 1000 ) % 10 ;
                if(timer>0) {
                    countsound = std::make_shared<SFX>(RESOURCE_DIR"/voice/06 Other/" + std::to_string(timer) + ".wav");//14s
                    countsound->Play();
                }
            }
            if(timer<0){timer=0;}
            if(timer==0) {
                Result=ChooseResult::GameOver;
                currentstate=ContinueSceneState::WaitForEnd;
                start_time=Time::GetElapsedTimeMs();
                gameoversound->Play();
                m_BGM->Pause();
                gameover_picture->SetVisible(true);
            }
            if(timer>0&&Input::IsKeyDown(Keycode::RETURN)) {
                player_face=std::make_shared<ImageSpace>(player->GetFace());
                player_face->SetDrawData({{-280, 50},0,{1,1}},
                        {300,player_face->GetScaledSize().y*300/player_face->GetScaledSize().x},
                        2.0f);
                continuesound->Play();
                Result=ChooseResult::Continue;
                currentstate=ContinueSceneState::WaitForEnd;
                start_time=Time::GetElapsedTimeMs();
            }
        }
        else if(currentstate==ContinueSceneState::WaitForEnd) {
            if(GetPassedTime()>3500) {
                SenseEnd=true;
            }
        }
        time_picture = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/ContinueScene/" + std::to_string(timer) + ".png");
        time_picture->SetDrawData({{350, 0},0,{1,1}},
            time_picture->GetScaledSize()*glm::vec2{0.65,0.65},
            2.0f);
    }
    void ContinueScene::Render() {
        AllPictures={player_face,time_picture,gameover_picture};
        for (const auto& image : AllPictures) {
            image->custom_Draw();
        }
    }
}