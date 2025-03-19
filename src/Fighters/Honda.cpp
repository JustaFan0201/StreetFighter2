//
// Created by asus on 2025/2/27.
//

#include "Fighters/Honda.hpp"
namespace Util {
    Honda::Honda():Fighter("Honda",{0,0}){
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Honda/Honda_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Honda/Honda_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/HondaTheme.mp3");
        country_position={{28, 168},0,{1,1}};
        BackgroundInit(7);
        Honda::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Honda::LoadAnimations() {
        animations[FighterState::Idle]=ActionInit(4,"Idle");
        animations[FighterState::Backward]=ActionInit(4,"Backward");
        animations[FighterState::Forward]=ActionInit(4,"Forward");
        animations[FighterState::LP]=ActionInit(5,"LP");
        animations[FighterState::MP]=ActionInit(7, "MP");
    }
}