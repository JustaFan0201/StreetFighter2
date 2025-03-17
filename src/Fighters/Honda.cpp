//
// Created by asus on 2025/2/27.
//

#include "Fighters/Honda.hpp"
namespace Util {
    Honda::Honda():Fighter("Honda",0){
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Honda/Honda_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Honda/Honda_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/HondaTheme.mp3");
        country_position={{28, 168},0,{1,1}};
        BackgroundInit(7);
        Idle=ActionInit(4,"Idle");
        Back=ActionInit(4,"Back");
        Forward=ActionInit(4,"Forward");
        LP=ActionInit(5,"LP");
        MP=ActionInit(7, "MP");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );

    }
}