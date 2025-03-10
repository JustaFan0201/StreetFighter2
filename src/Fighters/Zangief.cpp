//
// Created by asus on 2025/2/27.
//

#include "Fighters/Zangief.hpp"
namespace Util {
    Zangief::Zangief(): Fighter("Zangief",5) {
        face=std::string("../sencepicture/Fighters/Zangief/Zangief_face.png");
        nametag=std::string("../sencepicture/Fighters/Zangief/Zangief_nametag.png");
        country=std::string("../sencepicture/slect/ussr.png");
        m_BGM=std::make_shared<BGM>("../music/11 Zangief.mp3");
        country_position={{-244, 220},0,{1,1}};
        BackgroundInit(5);
    }
}