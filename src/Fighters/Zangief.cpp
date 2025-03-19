//
// Created by asus on 2025/2/27.
//

#include "Fighters/Zangief.hpp"
namespace Util {
    Zangief::Zangief(): Fighter("Zangief",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Zangief/Zangief_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Zangief/Zangief_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/ussr.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/ZangiefTheme.mp3");
        country_position={{-244, 220},0,{1,1}};
        BackgroundInit(8);
        Zangief::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Zangief::LoadAnimations() {
        animations[FighterState::Idle]=ActionInit(4,"Idle");
        animations[FighterState::Backward]=ActionInit(6,"Backward");
        animations[FighterState::Forward]=ActionInit(6,"Forward");
        animations[FighterState::LP]=ActionInit(4,"LP");
        animations[FighterState::MP]=ActionInit(4, "MP");
    }
}