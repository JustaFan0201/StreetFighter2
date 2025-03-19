#include "Fighters/Fighter.hpp"
#include <iostream>
namespace Util {
    void Fighter::StateDealing() {
        if (currentState == FighterState::Idle) {IdleStateUpload();}
        else if (currentState == FighterState::Forward) {ForwardStateUpload();}
        else if (currentState == FighterState::Backward) {BackwardStateUpload();}
        else if (currentState == FighterState::LP) {LPStateUpload();}
        else if (currentState == FighterState::MP) {MPStateUpload();}
        else if (currentState == FighterState::JumpUP) {JumpUPStateUpload();}
        else if (currentState == FighterState::LK) {LKStateUpload();}
        else if (currentState == FighterState::MK) {MKStateUpload();}
        else if (currentState == FighterState::HK) {LKStateUpload();}
    }
    void Fighter::ChangeState(FighterState newState) {
        if (currentState != newState) {
            currentState = newState;
            switch (currentState) {
                case FighterState::Idle:
                    IdleStateEnter();
                break;
                case FighterState::Forward:
                    ForwardStateEnter();
                break;
                case FighterState::Backward:
                    BackwardStateEnter();
                break;
                case FighterState::LP:
                    LPStateEnter();
                break;
                case FighterState::MP:
                    MPStateEnter();
                break;
                case FighterState::JumpUP:
                    JumpUPStateEnter();
                break;
                case FighterState::LK:
                    LKStateEnter();
                break;
                case FighterState::MK:
                    MKStateEnter();
                break;
                case FighterState::HK:
                    HKStateEnter();
                break;
                default:
                    break;
            }
        }
    }
    void Fighter::SetAnimation(FighterState action,std::vector<int> intervals) {
        if (animations.find(action) != animations.end()) {
            ActionNow->SetDrawable(std::make_shared<Animation>(animations[action], true, 60, true));
            ActionNow->SetFrameIntervals(intervals);
        }
    }

    void Fighter::BackgroundInit(int picture_number) {
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/Battle/"+ GetName() +"/frame ("+num+").png";
            stage_background.push_back(filename);
        }
    }

    std::vector<std::string> Fighter::ActionInit(int picture_number,std::string Action) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/Fighters/"+ GetName() +"/"+ Action +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        return Allframe;
    }

    void Fighter::InitPosition(glm::vec2 position, int side) {
        float size_x=ActionNow->GetOriginalSize().x * 3;
        float size_y=ActionNow->GetOriginalSize().y * 3;
        ActionNow->SetDrawData({position, 0, {side, 1}},
                               {size_x, size_y},
                               2.0f);
        direction = side;
        if(direction==1){ActionNow->SetLeftDownBeCenter();}
        else if(direction==-1){ActionNow->SetRightDownBeCenter();}
        currentState = FighterState::Idle;
    }

    void Fighter::ReSize() {
        if (!ActionNow) return;
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
        if (ActionNow->m_Transform.translation.y < StageFloor+ActionNow->GetCustomSize().y/2) {
            ActionNow->m_Transform.translation.y=StageFloor+ActionNow->GetCustomSize().y/2;
        }
    }

    void Fighter::Upload(std::shared_ptr<Core::Context> context) {
        StateDealing();
        glm::vec2 position={ActionNow->GetTransform().translation.x+velocity.x*Time::GetDeltaTimeMs()/1000,
            ActionNow->GetTransform().translation.y+velocity.y*Time::GetDeltaTimeMs()/1000};
        ActionNow->SetTransform({position,0,{direction,1}});
        ReSize();
        BorderDection(context->GetWindowWidth()/2);
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
    }
}
