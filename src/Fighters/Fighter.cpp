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
        ActionNow->SetDrawData({position, 0, {side, 1}},
                               {ActionNow->GetScaledSize().x * 3, ActionNow->GetScaledSize().y * 3},
                               2.0f);
        direction = side;
        ActionNow->SetMatchFloor(Floor);
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
            // 當角色朝右時 (direction > 0)，A 為後退；朝左時 (direction < 0)，A 為前進
            ActionNow->m_Transform.translation.x -= velocity * Time::GetDeltaTimeMs() / 1000;
            now = (direction > 0) ? State::Back : State::Forward;
        }
        else if (Input::IsKeyPressed(Keycode::D)) {
            // 當角色朝右時 (direction > 0)，D 為前進；朝左時 (direction < 0)，D 為後退
            ActionNow->m_Transform.translation.x += velocity * Time::GetDeltaTimeMs() / 1000;
            now = (direction > 0) ? State::Forward : State::Back;
        }
        else if (Input::IsKeyPressed(Keycode::J)) {
            now = State::Lightpunch;
        }
        else if (Input::IsKeyPressed(Keycode::U)) {
            now = State::Heavypunch;
        }
        else {
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
            ActionNow->SetDrawable(std::make_shared<Util::Animation>(newFrames, true, 60, true));
        }

        //------------------------------------------------------------------之後搬走-----------------------------------------------
        if (now == State::Lightpunch || now == State::Heavypunch) {
            if (direction > 0) {
                ActionNow->SetDrawData(
                {{ActionNow->m_Transform.translation.x+2, ActionNow->m_Transform.translation.y}, 0, {direction, 1}},
                {ActionNow->GetScaledSize().x * 3, ActionNow->GetScaledSize().y * 3},
                2.0f
                );
            }
            else {
                ActionNow->SetDrawData(
                {{ActionNow->m_Transform.translation.x-2, ActionNow->m_Transform.translation.y}, 0, {direction, 1}},
                {ActionNow->GetScaledSize().x * 3, ActionNow->GetScaledSize().y * 3},
                2.0f
                );
            }
        }
        else {ActionNow->SetDrawData(
           {ActionNow->m_Transform.translation, 0, {direction, 1}},
           {ActionNow->GetScaledSize().x * 3, ActionNow->GetScaledSize().y * 3},
           2.0f
           );
        }

        //-----------------------------------------------------------------------------------------------------------------

        int MaxWidth=context->GetWindowWidth()/2;
        if (ActionNow->m_Transform.translation.x > MaxWidth - abs(ActionNow->GetScaledSize().x) * 3 / 2||
            ActionNow->m_Transform.translation.x < -MaxWidth + abs(ActionNow->GetScaledSize().x) * 3 / 2) {
            // 限制角色位置


            ActionNow->m_Transform.translation.x = std::clamp(ActionNow->m_Transform.translation.x,
                -MaxWidth + abs(ActionNow->GetScaledSize().x) * 3 / 2,
                MaxWidth - abs(ActionNow->GetScaledSize().x) * 3 / 2);
            // 反轉角色朝向
        }
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
    }

}
