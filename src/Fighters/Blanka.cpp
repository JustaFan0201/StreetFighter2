//
// Created by asus on 2025/2/27.
//

#include "Fighters/Blanka.hpp"
namespace Util {
    Blanka::Blanka(): Fighter("Blanka",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Blanka/Blanka_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Blanka/Blanka_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/brazil.png");
        country_position={{323, 23},0,{1,1}};
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/BlankaTheme.mp3");
        m_name = "Blanka";
        BackgroundInit(4);
        StateInit();
        Blanka::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Blanka::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(5,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(3, "MP");
    }
}
