//
// Created by FanFan on 2025/1/27.
//

// StartScene.hpp
#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP

#include "Scene.hpp"
namespace Util {
    class StartScene : public Scene {
    private:
        int mode=0;//0=story 1=battle
        bool m_WaitingForEnter=true;
        std::shared_ptr<SFX> soundEffect = std::make_shared<Util::SFX>("../voice/01 Select Screen & World Map/SFII_01 - Mode Select.wav");
        std::shared_ptr<Word> Word_1 = std::make_shared<Word>("../streetfighter.ttf", 32, "Story mode", Color(255, 127, 80));//story
        std::shared_ptr<Word> Word_2 = std::make_shared<Word>("../streetfighter.ttf", 32, "Battle mode", Color(255, 255, 255));//battle
    public:
        StartScene();
        void Init() override;   // 初始化
        void Update() override; // 更新場景
        void Render() override; // 渲染圖片
        int getmode() const { return mode; }
    };

} // namespace Util

#endif /* STARTSCENE_HPP */
