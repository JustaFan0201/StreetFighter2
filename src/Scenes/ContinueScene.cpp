//
// Created by asus on 2025/5/24.
//

#include "Scenes/ContinueScene.hpp"
namespace Util {
    void ContinueScene::Init(std::shared_ptr<Core::Context> context){
        start_time=Time::GetElapsedTimeMs();
        countsound = std::make_shared<SFX>(RESOURCE_DIR"/voice/06 Other/9.wav");//14s
        countsound->Play();
        continuesound=std::make_shared<SFX>(RESOURCE_DIR"/voice/01 Select Screen & World Map/SFII_03 - Selection.wav");
        player_face=std::make_shared<ImageSpace>(player->GetLossFace());

        player_face->SetDrawData({{-280, 50},0,{1,1}},
                player_face->GetScaledSize()*glm::vec2{3,3},
                2.0f);
        time_picture=std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/LossScene/9.png");
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
            }
            if(timer>0&&Input::IsKeyDown(Keycode::RETURN)) {
                player_face=std::make_shared<ImageSpace>(player->GetFace());
                player_face->SetDrawData({{-280, 50},0,{1,1}},
                        player_face->GetScaledSize()*glm::vec2{3,3},
                        2.0f);
                continuesound->Play();
                Result=ChooseResult::Continue;
                currentstate=ContinueSceneState::WaitForEnd;
                start_time=Time::GetElapsedTimeMs();
            }
        }
        else if(currentstate==ContinueSceneState::WaitForEnd) {
            if(GetPassedTime()>3000) {
                SenseEnd=true;
            }
        }
        time_picture = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/LossScene/" + std::to_string(timer) + ".png");
        time_picture->SetDrawData({{350, 0},0,{1,1}},
            time_picture->GetScaledSize()*glm::vec2{0.65,0.65},
            2.0f);
    }
    void ContinueScene::Render() {
        AllPictures={player_face,time_picture};
        for (const auto& image : AllPictures) {
            image->custom_Draw();
        }
    }
}