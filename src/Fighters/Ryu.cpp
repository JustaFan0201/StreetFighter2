//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ryu.hpp"
namespace Util {
    Ryu::Ryu() {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Ryu/Ryu_face.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/japan.png");
        country_position={{14,90},0,{1,1}};
    }
}