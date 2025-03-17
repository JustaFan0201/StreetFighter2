//
// Created by asus on 2025/2/27.
//

#include "Fighters/Blanka.hpp"
namespace Util {
    Blanka::Blanka(): Fighter("Blanka",0) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Blanka/Blanka_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Blanka/Blanka_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/brazil.png");
        country_position={{323, 23},0,{1,1}};
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/BlankaTheme.mp3");
        BackgroundInit(4);
    }
}