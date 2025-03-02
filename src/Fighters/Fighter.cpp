//
// Created by asus on 2025/2/27.
//

#include "Fighters/Fighter.hpp"
void Util::Fighter::BackgroundInit(int picture_number) {
    for (int i = 1; i <= picture_number; i++) {
        std::string num = std::to_string(i);
        std::string filename = "../sencepicture/Battle/"+ GetName() +"/frame ("+num+").png";
        stage_background.push_back(filename);
    }
}
