//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ken.hpp"
namespace Util {
    Ken::Ken() {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Ken/Ken_face.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/usa.png");
        country_position={{338, 245},0,{1,1}};
    }
}