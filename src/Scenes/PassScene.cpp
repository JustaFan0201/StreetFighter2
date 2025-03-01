//
// Created by FanFan on 2025/2/28.
//

#include "Scenes/PassScene.hpp"
namespace Util {
    void PassScene::Init() {
        std::vector<std::string> frames;
        for (int i = 1; i <= 30; ++i) {
            std::string num = std::to_string(i);
            if (i < 10) num = "00" + num;
            else if (i < 100) num = "0" + num;
            std::string filename = "../sencepicture/Pass/Speed/ezgif-frame-" + num + ".png";
            frames.push_back(filename);
        }

        m_Animation = std::make_shared<AnimationSpace>(
            frames,
            true,
            50,
            true,
            0
        );//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑過場動畫
        start_time=Time::GetElapsedTimeMs();
        vs->SetFullScreen();
        m_Animation->SetFullScreen();

        m_BGM = std::make_shared<BGM>("../music/04 Start Battle.mp3");//14s
        m_BGM->SetVolume(30);
        m_BGM->Play(0);

        vs->SetZIndex(3.0f);
        player_face->SetDrawData({{-350, 0},0,{1,1}},
                {288, 306},
                2.0f);
        enemy_face->SetDrawData({{350, 0},0,{-1,1}},
                {288, 306},
                2.0f);
        player_nametag->SetDrawData({{-350, -200},0,{1,1}},
                {288,63},
                2.0f);
        enemy_nametag->SetDrawData({{350, -200},0,{1,1}},
                {288,63},
                2.0f);
    }
    void PassScene::Update() {
        if (Time::GetElapsedTimeMs() - start_time > 5000){
            SenseEnd=true;
        }
    }
    void PassScene::Render() {
        AllPictures={player_face,enemy_face,player_nametag,enemy_nametag,vs};
        for (const auto& i : AllPictures) {
            i->custom_Draw();
        }
        m_Animation->custom_Draw();
    }
}
