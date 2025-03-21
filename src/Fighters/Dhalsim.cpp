//
// Created by asus on 2025/2/27.
//

#include "Fighters/Dhalsim.hpp"
namespace Util {
    Dhalsim::Dhalsim(): Fighter("Dhalsim",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Dhalsim/Dhalsim_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Dhalsim/Dhalsim_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/india.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/DhalsimTheme.mp3");
        m_name="Dhalsim";
        country_position={{-228, 97},0,{1,1}};
        BackgroundInit(13);
        StateInit();
        Dhalsim::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Dhalsim::LoadAnimations() {
        animations[FighterState::Idle]=ActionInit(6,"Idle");
        animations[FighterState::Backward]=ActionInit(7,"Backward");
        animations[FighterState::Forward]=ActionInit(7,"Forward");
        animations[FighterState::LP]=ActionInit(3,"LP");
        animations[FighterState::MP]=ActionInit(4, "MP");
        animations[FighterState::HP]=ActionInit(4, "HP");
    }
}