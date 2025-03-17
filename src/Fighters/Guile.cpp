//
// Created by asus on 2025/2/27.
//

#include "Fighters/Guile.hpp"
namespace Util {
    Guile::Guile():Fighter("Guile",0){
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/GuileTheme.mp3");
        country_position={{350, 140},0,{1,1}};
        BackgroundInit(13);
        Idle=ActionInit(6,"Idle");
        Back=ActionInit(5,"Back");
        Forward=ActionInit(5,"Forward");
        LP=ActionInit(3,"LP");
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