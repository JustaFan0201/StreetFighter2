//
// Created by USER on 2025/5/23.
//

#include "Scenes/WinLossScene.hpp"
namespace Util {
    void WinLossScene::Init(std::shared_ptr<Core::Context> context){
        start_time=Time::GetElapsedTimeMs();
        m_BGM = std::make_shared<BGM>(RESOURCE_DIR"/music/13 End Battle.mp3");//14s
        m_BGM->SetVolume(40);
        m_BGM->Play(0);
        switch(result) {
            case FinalResult::Player1Win:
                player_face=std::make_shared<ImageSpace>(player->GetFace());
                enemy_face=std::make_shared<ImageSpace>(enemy->GetLossFace());
                winword=std::make_shared<ImageSpace>(player->GetWinWord());
                break;
            case FinalResult::Player2Win:
                player_face=std::make_shared<ImageSpace>(player->GetLossFace());
                enemy_face=std::make_shared<ImageSpace>(enemy->GetFace());
                winword=std::make_shared<ImageSpace>(enemy->GetWinWord());
                break;
            default:
                player_face=std::make_shared<ImageSpace>(player->GetFace());
                enemy_face=std::make_shared<ImageSpace>(enemy->GetFace());
                winword=std::make_shared<ImageSpace>(player->GetWinWord());
                break;
        }
        player_face->SetDrawData({{-350, 50},0,{1,1}},
                player_face->GetScaledSize()*glm::vec2{3,3},
                2.0f);
        enemy_face->SetDrawData({{350, 50},0,{-1,1}},
                enemy_face->GetScaledSize()*glm::vec2{3,3},
                2.0f);
        winword->SetDrawData({{0, -200},0,{1,1}},
                winword->GetScaledSize()*glm::vec2{0.65,0.65},
                2.0f);
    }
    void WinLossScene::Update(std::shared_ptr<Core::Context> context){
        if(GetPassedTime()>5000) {
            SenseEnd=true;
        }
    }
    void WinLossScene::Render() {
        AllPictures={player_face,enemy_face,winword};
        for (const auto& image : AllPictures) {
            image->custom_Draw();
        }
    }
}