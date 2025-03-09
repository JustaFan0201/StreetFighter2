//
// Created by asus on 2025/2/27.
//

#include "Fighters/Guile.hpp"
namespace Util {
    Guile::Guile():Fighter("Guile",5){
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Guile/Guile_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Guile/Guile_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>("../music/08 Guile.mp3");
        country_position={{350, 140},0,{1,1}};
        BackgroundInit(13);
    }
}