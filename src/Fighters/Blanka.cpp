//
// Created by asus on 2025/2/27.
//

#include "Fighters/Blanka.hpp"
namespace Util {
    Blanka::Blanka(): Fighter("Blanka",5) {
        face=std::string("../sencepicture/Fighters/Blanka/Blanka_face.png");
        nametag=std::string("../sencepicture/Fighters/Blanka/Blanka_nametag.png");
        country=std::string("../sencepicture/slect/brazil.png");
        country_position={{323, 23},0,{1,1}};
        m_BGM=std::make_shared<BGM>("../music/07 Blanka.mp3");
        BackgroundInit(4);
    }
}