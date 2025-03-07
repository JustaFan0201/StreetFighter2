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
        //enter音效
        std::shared_ptr<SFX> soundEffect = std::make_shared<Util::SFX>("../voice/01 Select Screen & World Map/SFII_01 - Mode Select.wav");
        //Story跟Battle文字顯示
        std::shared_ptr<Word> Word_1 = std::make_shared<Word>("../streetfighter.ttf", 32, "Story mode", Color(255, 127, 80));//story
        std::shared_ptr<Word> Word_2 = std::make_shared<Word>("../streetfighter.ttf", 32, "Battle mode", Color(255, 255, 255));//battle
    public:
        StartScene();
        void Init() override;
        void Update() override;
        void Render() override;
        int getmode() const { return mode; }//取得當前模式
    };

} // namespace Util

#endif /* STARTSCENE_HPP */
