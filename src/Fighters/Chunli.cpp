//
// Created by asus on 2025/2/27.
//

#include "Fighters/Chunli.hpp"
namespace Util {
    Chunli::Chunli() {
        face=std::make_shared<ImageSpace>("../sencepicture/Fighters/Chunli/Chunli_face.png");
        country=std::make_shared<ImageSpace>("../sencepicture/slect/china.png");
        country_position={{-113, 193},0,{1,1}};
    }
}