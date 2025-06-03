//
// Created by asus on 2025/6/3.
//
#include "Scenes/EndingScene.hpp"
namespace Util {
    EndingScene::EndingScene() = default;
    void EndingScene::Init(std::shared_ptr<Core::Context> context) {
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/23 Ryu's Ending.mp3");
        m_BGM->Play();
        Win=std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Ending/YouWin.png");
        Win->SetDrawData({{0, 0},0,{1,1}},
        Win->GetScaledSize()*glm::vec2{5,5},10.0f);
        start_time=Time::GetElapsedTimeMs();
    }
    void EndingScene::Update(std::shared_ptr<Core::Context> context) {
        if(GetPassedTime()>5000) {
            SceneEnd=true;
        }
    }
    void EndingScene::Render() {
        AllPictures={Win};
        for(const auto& image : AllPictures) {
            image->custom_Draw();
        }
    }
}