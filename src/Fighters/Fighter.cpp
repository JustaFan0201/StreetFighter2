#include "Fighters/Fighter.hpp"
#include <iostream>
namespace Util {
    void Fighter::IdleState::Enter(std::shared_ptr<Fighter> fighter) {
        fighter->ActionNow->SetDrawable(std::make_shared<Animation>(fighter->Idle, true, 60, true));
    }
    void Fighter::IdleState::Update(std::shared_ptr<Fighter> fighter) {
        fighter->velocity=0;
        if (Input::IsKeyPressed(Keycode::D)) {
            if (fighter->direction > 0) {fighter->ChangeState(std::make_shared<ForwardState>());}
            else {fighter->ChangeState(std::make_shared<BackState>());}
        }
        else if (Input::IsKeyPressed(Keycode::A)) {
            if (fighter->direction < 0) {fighter->ChangeState(std::make_shared<ForwardState>());}
            else {fighter->ChangeState(std::make_shared<BackState>());}
        }
        else if (Input::IsKeyPressed(Keycode::T)) {
            fighter->ChangeState(std::make_shared<LPState>());
        }
        else if (Input::IsKeyPressed(Keycode::Y)) {
            fighter->ChangeState(std::make_shared<MPState>());
        }
    }

    void Fighter::ForwardState::Enter(std::shared_ptr<Fighter> fighter) {
        fighter->ActionNow->SetDrawable(std::make_shared<Animation>(fighter->Forward, true, 60, true));
    }
    void Fighter::ForwardState::Update(std::shared_ptr<Fighter> fighter) {
        fighter->velocity=150;
        if (Input::IsKeyUp(Keycode::D)&&fighter->direction>0||Input::IsKeyUp(Keycode::A)&&fighter->direction<0) {
            fighter->ChangeState(std::make_shared<IdleState>());
        }
    }

    void Fighter::BackState::Enter(std::shared_ptr<Fighter> fighter) {
        fighter->ActionNow->SetDrawable(std::make_shared<Animation>(fighter->Back, true, 60, true));
    }
    void Fighter::BackState::Update(std::shared_ptr<Fighter> fighter) {
        fighter->velocity=-150;
        if (Input::IsKeyUp(Keycode::A)&&fighter->direction>0||Input::IsKeyUp(Keycode::D)&&fighter->direction<0) {
            fighter->ChangeState(std::make_shared<IdleState>());
        }
    }

    void Fighter::LPState::Enter(std::shared_ptr<Fighter> fighter) {
        fighter->ActionNow->SetDrawable(std::make_shared<Animation>(fighter->LP, true, 60, true));
    }
    void Fighter::LPState::Update(std::shared_ptr<Fighter> fighter) {
        if (Input::IsKeyUp(Keycode::T)) {
            fighter->ChangeState(std::make_shared<IdleState>());
        }
    }
    void Fighter::MPState::Enter(std::shared_ptr<Fighter> fighter) {
        fighter->ActionNow->SetDrawable(std::make_shared<Animation>(fighter->MP, true, 60, true));
    }
    void Fighter::MPState::Update(std::shared_ptr<Fighter> fighter) {
        if (Input::IsKeyUp(Keycode::Y)) {
            fighter->ChangeState(std::make_shared<IdleState>());
        }
    }

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
        if (!ActionNow) return;  // 確保 ActionNow 不為 nullptr
        float size_x = ActionNow->GetOriginalSize().x * 3;
        float size_y = ActionNow->GetOriginalSize().y * 3;
        ActionNow->SetDrawData(
            {ActionNow->m_Transform.translation, 0, {direction, 1}},
            {size_x, size_y},
            2.0f
        );
    }

    void Fighter::ChangeState(std::shared_ptr<FighterState> newState) {
        currentState = newState;
        if (currentState) {
            currentState->Enter(shared_from_this());
        }
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
        ActionNow->SetTransform({{ActionNow->GetTransform().translation.x+direction*velocity*Time::GetDeltaTimeMs()/1000,ActionNow->GetTransform().translation.y},0,{direction,1}});
        if (currentState) {
            currentState->Update(shared_from_this());
        }
        ReSize();
        BorderDection(context->GetWindowWidth()/2);
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
    }

}
