//
// Created by asus on 2025/2/27.
//

#include "Fighters/Fighter.hpp"
namespace Util {
    void Fighter::BackgroundInit(int picture_number) {
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = "../sencepicture/Battle/"+ GetName() +"/frame ("+num+").png";
            stage_background.push_back(filename);
        }
    }
    std::vector<std::string> Fighter::ActionInit(int picture_number,std::string Action) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = "../sencepicture/Fighters/"+ GetName() +"/"+ Action +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        return Allframe;
    }
    void Fighter::Upload() {
        if (Input::IsKeyDown(Keycode::A)) {
            ActionNow->m_Transform.translation.x -= 5;
        }
        if (Input::IsKeyDown(Keycode::D)) {
            ActionNow->m_Transform.translation.x += 5;
        }
    }
    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
    }
}