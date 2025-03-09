//
// Created by asus on 2025/2/27.
//

#include "Fighters/Chunli.hpp"
namespace Util {
    Chunli::Chunli(): Fighter("Chunli",5) {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Chunli/Chunli_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Chunli/Chunli_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/china.png");
        m_BGM=std::make_shared<BGM>("../music/10 Chun Li.mp3");
        country_position={{-113, 193},0,{1,1}};
        BackgroundInit(29);
    }
}