//
// Created by asus on 2025/2/27.
//

#include "Fighters/Chunli.hpp"
namespace Util {
    Chunli::Chunli(): Fighter("Chunli",200) {
        face=std::string("../sencepicture/Fighters/Chunli/Chunli_face.png");
        nametag=std::string("../sencepicture/Fighters/Chunli/Chunli_nametag.png");
        country=std::string("../sencepicture/slect/china.png");
        m_BGM=std::make_shared<BGM>("../music/10 Chun Li.mp3");
        country_position={{-113, 193},0,{1,1}};
        BackgroundInit(29);
        Idle=ActionInit(4,"Idle");
        Back=ActionInit(12,"Back");
        Forward=ActionInit(12,"Forward");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );
    }
}