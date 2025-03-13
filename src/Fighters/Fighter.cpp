#include "Fighters/Fighter.hpp"
#include <iostream>
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

    void Fighter::InitPosition(glm::vec2 position, int side, float Floor) {
        float size_x=ActionNow->GetOriginalSize().x * 3;
        float size_y=ActionNow->GetOriginalSize().y * 3;
        ActionNow->SetDrawData({position, 0, {side, 1}},
                               {size_x, size_y},
                               2.0f);
        direction = side;
        ActionNow->SetMatchFloor(Floor);
    }
    void Fighter::ReSize() {
        float size_x = ActionNow->GetOriginalSize().x * 3;
        float size_y = ActionNow->GetOriginalSize().y * 3;
        ActionNow->SetDrawData(
            {ActionNow->m_Transform.translation, 0, {direction, 1}},
            {size_x, size_y},
            2.0f
        );
    }
    void Fighter::BorderDection(int MaxWidth) {
        if (ActionNow->m_Transform.translation.x > MaxWidth - abs(ActionNow->GetCustomSize().x) / 2||
            ActionNow->m_Transform.translation.x < -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2) {
            ActionNow->m_Transform.translation.x = std::clamp(ActionNow->m_Transform.translation.x,
                -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2,
                MaxWidth - abs(ActionNow->GetCustomSize().x)  / 2);
            }
    }

    void Fighter::Upload(std::shared_ptr<Core::Context> context) {
        State previous_state = now; // 記錄之前的狀態
        if (recoveryTime > 0) {
            recoveryTime -= Time::GetDeltaTimeMs() / 1000;  // 減少後搖時間
            if (recoveryTime <= 0) {
                recoveryTime = 0;  // 確保不會變成負數
                now = State::Idle; // 後搖結束回到待機狀態
            }
            return; // 在後搖期間，禁止其他動作
        }
        // 移動判斷
        if (Input::IsKeyPressed(Keycode::A)) {
            ActionNow->m_Transform.translation.x -= velocity * Time::GetDeltaTimeMs() / 1000;
            now = (direction > 0) ? State::Back : State::Forward;
        }
        else if (Input::IsKeyPressed(Keycode::D)) {
            ActionNow->m_Transform.translation.x += velocity * Time::GetDeltaTimeMs() / 1000;
            now = (direction > 0) ? State::Forward : State::Back;
        }
        else if (Input::IsKeyPressed(Keycode::J)) {
            ActionNow->SetTransform({{ActionNow->m_Transform.translation.x+2*direction, ActionNow->m_Transform.translation.y}, 0, {direction, 1}});
            ReSize();
            now = State::Lightpunch;
        }
        else if (Input::IsKeyPressed(Keycode::U)) {
            ActionNow->SetTransform({{ActionNow->m_Transform.translation.x+2*direction, ActionNow->m_Transform.translation.y}, 0, {direction, 1}});
            ReSize();
            now = State::Heavypunch;
        }
        else {
            ReSize();
            now = State::Idle;
        }

        // 如果狀態改變，則更換動畫
        if (now != previous_state) {
            std::vector<std::string> newFrames;
            switch (now) {
                case State::Idle:
                    newFrames = Idle;
                    break;
                case State::Back:
                    newFrames = Back;
                    break;
                case State::Forward:
                    newFrames = Forward;
                    break;
                case State::Lightpunch:
                    newFrames = Lightpunch;
                    break;
                case State::Heavypunch:
                    newFrames = Heavypunch;
                    break;
            }
            ActionNow->SetDrawable(std::make_shared<Animation>(newFrames, true, 60, true));
        }
        BorderDection(context->GetWindowWidth()/2);
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
    }

}
