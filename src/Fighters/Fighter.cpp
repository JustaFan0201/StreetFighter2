#include "Fighters/Fighter.hpp"
#include <iostream>
namespace Util {
    void Fighter::ChangeState(FighterState newState) {
        if (currentState != newState) {
            currentState = newState;
            auto currentEnter = StateEnter.find(currentState);
            if (currentEnter != StateEnter.end()) {
                currentEnter->second();
            }
        }
    }
    void Fighter::SetAnimation(FighterState action,std::vector<int> intervals,std::vector<glm::vec2> offsets) {
        if (animations.find(action) != animations.end()) {
            ActionNow->SetDrawable(std::make_shared<Animation>(animations[action], true, 60, true));
            ActionNow->SetFrameIntervals(intervals);
            ActionNow->Setoffset(offsets);
        }
    }

    void Fighter::BackgroundInit(int picture_number) {
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/Battle/"+ GetName() +"/frame ("+num+").png";
            stage_background.push_back(filename);
        }
    }

    void Fighter::StateInit() {
        StateEnter[FighterState::Idle] = std::bind(&Fighter::IdleStateEnter, this);
        StateEnter[FighterState::Forward] = std::bind(&Fighter::WalkStateEnter, this);
        StateEnter[FighterState::Backward] = std::bind(&Fighter::WalkStateEnter, this);
        StateEnter[FighterState::JumpUP] = std::bind(&Fighter::JumpStateEnter, this);
        StateEnter[FighterState::JumpForward] = std::bind(&Fighter::JumpStateEnter, this);
        StateEnter[FighterState::JumpBackward] = std::bind(&Fighter::JumpStateEnter, this);
        StateEnter[FighterState::LP] = std::bind(&Fighter::LPStateEnter, this);
        StateEnter[FighterState::MP] = std::bind(&Fighter::MPStateEnter, this);
        StateEnter[FighterState::LK] = std::bind(&Fighter::LKStateEnter, this);
        StateEnter[FighterState::MK] = std::bind(&Fighter::MKStateEnter, this);
        StateEnter[FighterState::HK] = std::bind(&Fighter::HKStateEnter, this);

        StateUpload[FighterState::Idle] = std::bind(&Fighter::IdleStateUpload, this);
        StateUpload[FighterState::Forward] = std::bind(&Fighter::WalkStateUpload, this);
        StateUpload[FighterState::Backward] = std::bind(&Fighter::WalkStateUpload, this);
        StateUpload[FighterState::JumpUP] = std::bind(&Fighter::JumpStateUpload, this);
        StateUpload[FighterState::JumpForward] = std::bind(&Fighter::JumpStateUpload, this);
        StateUpload[FighterState::JumpBackward] = std::bind(&Fighter::JumpStateUpload, this);
        StateUpload[FighterState::LP] = std::bind(&Fighter::LPStateUpload, this);
        StateUpload[FighterState::MP] = std::bind(&Fighter::MPStateUpload, this);
        StateUpload[FighterState::LK] = std::bind(&Fighter::LKStateUpload, this);
        StateUpload[FighterState::MK] = std::bind(&Fighter::MKStateUpload, this);
        StateUpload[FighterState::HK] = std::bind(&Fighter::HKStateUpload, this);
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
        if (ActionNow->m_Transform.translation.y < StageFloor) {
            ActionNow->m_Transform.translation.y=StageFloor;
        }
        std::cout<<GetName()<<"x and y :"<<ActionNow->m_Transform.translation.x<<ActionNow->m_Transform.translation.y<<std::endl;
    }

    void Fighter::Upload(std::shared_ptr<Core::Context> context) {
        auto currentEnter = StateUpload.find(currentState);
        currentEnter->second();

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
