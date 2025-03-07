//
// Created by asus on 2025/2/27.
//

#include "Fighters/Dhalsim.hpp"
namespace Util {
    Dhalsim::Dhalsim(): Fighter("Dhalsim") {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Dhalsim/Dhalsim_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Dhalsim/Dhalsim_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/india.png");
        m_BGM=std::make_shared<BGM>("../music/12 Dhalsim.mp3");
        country_position={{-228, 97},0,{1,1}};
        BackgroundInit(13);
    }
}