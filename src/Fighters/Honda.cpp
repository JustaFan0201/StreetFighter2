//
// Created by asus on 2025/2/27.
//

#include "Fighters/Honda.hpp"
namespace Util {
    Honda::Honda():Fighter("Honda",5){
        face=std::string("../sencepicture/Fighters/Honda/Honda_face.png");
        nametag=std::string("../sencepicture/Fighters/Honda/Honda_nametag.png");
        country=std::string("../sencepicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>("../music/06 E. Honda.mp3");
        country_position={{28, 168},0,{1,1}};
        BackgroundInit(7);
    }
}