//
// Created by asus on 2025/2/27.
//

#include "Fighters/Guile.hpp"
namespace Util {
    Guile::Guile():Fighter("Guile"){
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Guile/Guile_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Guile/Guile_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/usa.png");
        country_position={{350, 140},0,{1,1}};
        BackgroundInit(13);
    }
}