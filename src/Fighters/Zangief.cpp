//
// Created by asus on 2025/2/27.
//

#include "Fighters/Zangief.hpp"
namespace Util {
    Zangief::Zangief(): Fighter("Zangief",0) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Zangief/Zangief_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Zangief/Zangief_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/ussr.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/ZangiefTheme.mp3");
        country_position={{-244, 220},0,{1,1}};
        BackgroundInit(5);
        Idle=ActionInit(4,"Idle");
        Back=ActionInit(6,"Back");
        Forward=ActionInit(6,"Forward");
        LP=ActionInit(4,"LP");
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