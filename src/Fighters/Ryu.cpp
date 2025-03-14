//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ryu.hpp"
namespace Util {
    Ryu::Ryu(): Fighter("Ryu",0) {
        face=std::string("../sencepicture/Fighters/Ryu/Ryu_face.png");
        nametag=std::string("../sencepicture/Fighters/Ryu/Ryu_nametag.png");
        country=std::string("../sencepicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>("../music/05 Ryu.mp3");
        country_position={{14,90},0,{1,1}};
        BackgroundInit(15);

        Idle=ActionInit(5,"Idle");
        Back=ActionInit(6,"Back");
        Forward=ActionInit(6,"Forward");
        LP=ActionInit(2, "LP");
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