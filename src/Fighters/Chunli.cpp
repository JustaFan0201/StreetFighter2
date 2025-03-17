//
// Created by asus on 2025/2/27.
//

#include "Fighters/Chunli.hpp"
namespace Util {
    Chunli::Chunli(): Fighter("Chunli",0) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Chunli/Chunli_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Chunli/Chunli_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/china.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/ChunliTheme.mp3");
        country_position={{-113, 193},0,{1,1}};
        BackgroundInit(29);
        Idle=ActionInit(4,"Idle");
        Back=ActionInit(12,"Back");
        Forward=ActionInit(12,"Forward");
        LP=ActionInit(5,"LP");
        MP=ActionInit(5, "MP");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );
    }
}