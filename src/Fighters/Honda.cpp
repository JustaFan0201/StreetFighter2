//
// Created by asus on 2025/2/27.
//

#include "Fighters/Honda.hpp"
namespace Util {
    Honda::Honda():Fighter("Honda"){
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Honda/Honda_face.png");
        nametag=std::make_shared<ImageSpace>("../sencepicture/Fighters/Honda/Honda_nametag.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/japan.png");
        country_position={{28, 168},0,{1,1}};
        BackgroundInit(7);
    }
}