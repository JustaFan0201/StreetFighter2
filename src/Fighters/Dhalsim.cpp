//
// Created by asus on 2025/2/27.
//

#include "Fighters/Dhalsim.hpp"
namespace Util {
    Dhalsim::Dhalsim(): Fighter("Dhalsim",0) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Dhalsim/Dhalsim_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Dhalsim/Dhalsim_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/india.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/DhalsimTheme.mp3");
        country_position={{-228, 97},0,{1,1}};
        BackgroundInit(13);
        Idle=ActionInit(6,"Idle");
        Back=ActionInit(7,"Back");
        Forward=ActionInit(7,"Forward");
        LP=ActionInit(3,"LP");
        MP=ActionInit(4, "MP");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );
    }
}