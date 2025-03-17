//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ken.hpp"
namespace Util {
    Ken::Ken(): Fighter("Ken",0) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ken/Ken_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ken/Ken_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/KenTheme.mp3");
        country_position={{338, 245},0,{1,1}};
        BackgroundInit(14);
        Idle=ActionInit(5,"Idle");
        Back=ActionInit(6,"Back");
        Forward=ActionInit(6,"Forward");
        LP=ActionInit(3, "LP");
        MP=ActionInit(3, "MP");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );
    }

}