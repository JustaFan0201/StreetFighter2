//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ken.hpp"
namespace Util {
    Ken::Ken(): Fighter("Ken",200) {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Ken/Ken_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Ken/Ken_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>("../music/09 Ken.mp3");
        country_position={{338, 245},0,{1,1}};
        BackgroundInit(14);
        Idle=ActionInit(4,"Idle");
        Back=ActionInit(6,"Back");
        Forward=ActionInit(5,"Forward");
        ActionNow = std::make_shared<AnimationSpace>(
            Idle,
            true,
            60,
            true,
            5
        );
    }
}