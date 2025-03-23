#include "Fighters/Fighter.hpp"

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
            ActionNow->SetDrawable(std::make_shared<Animation>(animations[action], true, 60, false));
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
        StateEnter[FighterState::Idle] = [this] { IdleStateEnter(); };
        StateEnter[FighterState::Forward] = [this] { WalkStateEnter(); };
        StateEnter[FighterState::Backward] = [this] { WalkStateEnter(); };
        StateEnter[FighterState::JumpUP] = [this] { JumpStateEnter(); };
        StateEnter[FighterState::JumpForward] = [this] { JumpStateEnter(); };
        StateEnter[FighterState::JumpBackward] = [this] { JumpStateEnter(); };
        StateEnter[FighterState::Crouchdown] = [this] { CrouchdownEnter(); };
        StateEnter[FighterState::LP] = [this] { LPStateEnter(); };
        StateEnter[FighterState::MP] = [this] { MPStateEnter(); };
        StateEnter[FighterState::HP] = [this] { HPStateEnter(); };
        StateEnter[FighterState::LK] = [this] { LKStateEnter(); };
        StateEnter[FighterState::MK] = [this] { MKStateEnter(); };
        StateEnter[FighterState::HK] = [this] { HKStateEnter(); };

        StateUpload[FighterState::Idle] = [this] { IdleStateUpload(); };
        StateUpload[FighterState::Forward] = [this] { WalkStateUpload(); };
        StateUpload[FighterState::Backward] = [this] { WalkStateUpload(); };
        StateUpload[FighterState::JumpUP] = [this] { JumpStateUpload(); };
        StateUpload[FighterState::JumpForward] = [this] { JumpStateUpload(); };
        StateUpload[FighterState::JumpBackward] = [this] { JumpStateUpload(); };
        StateUpload[FighterState::Crouchdown] = [this] { CrouchdownUpload(); };
        StateUpload[FighterState::LP] = [this] { LPStateUpload(); };
        StateUpload[FighterState::MP] = [this] { MPStateUpload(); };
        StateUpload[FighterState::HP] = [this] { HPStateUpload(); };
        StateUpload[FighterState::LK] = [this] { LKStateUpload(); };
        StateUpload[FighterState::MK] = [this] { MKStateUpload(); };
        StateUpload[FighterState::HK] = [this] { HKStateUpload();};
        //ActionNow->AnimationPause();ActionNow->TestPictureoffset();
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
        FloorOfCharacter=ActionNow->GetOriginalSize().y * 3/2 + position.y;
        ActionNow->SetDrawData({position, 0, {side, 1}},
                               {size_x, size_y},
                               2.0f);
        direction = side;
        currentState = FighterState::Idle;

        if(BlackPicture!=nullptr) {
            BlackPicture->SetDrawData({position, 0, {1, 1}},
                                   pushbox.size[currentState],
                                   4.0f);
        }
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
        switch (currentState) {
            case FighterState::Idle:
            case FighterState::Forward:
            case FighterState::Backward:
            case FighterState::JumpUP:
            case FighterState::JumpForward:
            case FighterState::JumpBackward:
                if (ActionNow->m_Transform.translation.x > MaxWidth - abs(ActionNow->GetCustomSize().x) / 2||
                    ActionNow->m_Transform.translation.x < -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2) {
                    ActionNow->m_Transform.translation.x = std::clamp(ActionNow->m_Transform.translation.x,
                        -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2,
                        MaxWidth - abs(ActionNow->GetCustomSize().x)  / 2);
                    }
                if (ActionNow->m_Transform.translation.y < FloorOfCharacter) {
                    ActionNow->m_Transform.translation.y=FloorOfCharacter;
                }
                break;
            default:
                break;
        }
    }

    void Fighter::PrintPostion() {
        std::cout<<"{";
        for(auto i: Allofmouse) {
            std::cout <<"{"<< i.x<<","<< i.y<<"},";
        }
        std::cout <<"}"<< std::endl;
    }

    void Fighter::PostionTester() {
        if (Input::IsKeyDown(Keycode::MOUSE_MB)) {
            mouse = Input::GetCursorPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << mouse.x << ", " << mouse.y << ")" << std::endl;
            Allofmouse.clear();
        }
        if (Input::IsKeyDown(Keycode::MOUSE_RB)) {
            glm::vec2 Mouse=Input::GetCursorPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << Mouse.x << ", " << Mouse.y << ")" << std::endl;
            glm::vec2 Pos=mouse-Mouse;
            Allofmouse.push_back(Pos);
        }
    }

    void Fighter::PushBoxTester() {
        if(BlackPicture!=nullptr) {
            if(Input::IsKeyDown(Keycode::O)) {
                BlackPicture->SetVisible(true);
            }
            if(Input::IsKeyDown(Keycode::P)) {
                BlackPicture->SetVisible(false);
            }
        }
    }

    void Fighter::Upload(std::shared_ptr<Core::Context> context) {
        PostionTester();
        PushBoxTester();

        auto currentEnter = StateUpload.find(currentState);
        currentEnter->second();

        glm::vec2 position={ActionNow->GetTransform().translation.x+velocity.x*Time::GetDeltaTimeMs()/1000,
            ActionNow->GetTransform().translation.y+velocity.y*Time::GetDeltaTimeMs()/1000};

        ActionNow->SetTransform({position,0,{direction,1}});
        ReSize();
        BorderDection(context->GetWindowWidth()/2);

        if(BlackPicture!=nullptr) {
            BlackPicture->SetDrawData({GetCurrentOffsetPostion(), 0, {1, 1}},
                           pushbox.size[currentState],
                           4.0f);
        }
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();
        if(BlackPicture!=nullptr) {
            BlackPicture->custom_Draw();
        }
    }
}
