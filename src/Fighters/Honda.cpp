//
// Created by asus on 2025/2/27.
//

#include "Fighters/Honda.hpp"
namespace Util {
    Honda::Honda():Fighter("Honda",200){
        face=std::string("../sencepicture/Fighters/Honda/Honda_face.png");
        nametag=std::string("../sencepicture/Fighters/Honda/Honda_nametag.png");
        country=std::string("../sencepicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>("../music/06 E. Honda.mp3");
        country_position={{28, 168},0,{1,1}};
        BackgroundInit(7);
        Idle=ActionInit(4,"Idle");
        Back=ActionInit(4,"Back");
        Forward=ActionInit(4,"Forward");
        Lightpunch=ActionInit(7,"Lightpunch");
        Heavypunch=ActionInit(3, "Heavypunch");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );

    }
}