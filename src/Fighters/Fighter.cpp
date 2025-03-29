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
        StateEnter[FighterState::LP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::MP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::HP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::LK] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::MK] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::HK] = [this] { AttackStateEnter(); };

        StateUpload[FighterState::Idle] = [this] { IdleStateUpload(); };
        StateUpload[FighterState::Forward] = [this] { ForwardStateUpload(); };
        StateUpload[FighterState::Backward] = [this] { BackwardStateUpload(); };
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

    void Fighter::InitPosition(glm::vec2 position, int side,int Whichplayer) {
        float size_x=ActionNow->GetOriginalSize().x * 3;
        float size_y=ActionNow->GetOriginalSize().y * 3;
        FloorOfCharacter=ActionNow->GetOriginalSize().y * 3/2 + position.y;
        ActionNow->SetDrawData({{position.x,FloorOfCharacter}, 0, {side, 1}},
                               {size_x, size_y},
                               2.0f);
        direction = side;
        ChangeState(FighterState::Idle);
        ActionNow->SetLooping(true);
        controller->SetPlayerController(Whichplayer);

        pushboxPicture->SetDrawData({GetCurrentPosition(), 0, {1, 1}},GetCurrentPushbox(),4.0f);
        pushboxPicture->SetVisible(false);
        headPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[0], 0, {1, 1}},GetCurrentHurtboxSize()[0],7.0f);
        pushboxPicture->SetVisible(false);
        headPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[1], 0, {1, 1}},GetCurrentHurtboxSize()[1],8.0f);
        pushboxPicture->SetVisible(false);
        headPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[2], 0, {1, 1}},GetCurrentHurtboxSize()[2],9.0f);
        pushboxPicture->SetVisible(false);
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

    void Fighter::BorderDetection(int MaxWidth) {
        switch (currentState) {
            case FighterState::Idle:case FighterState::Forward:case FighterState::Backward:
            case FighterState::JumpUP:case FighterState::JumpForward:case FighterState::JumpBackward:
            case FighterState::Crouchdown:
                if (GetCurrentPosition().x > MaxWidth - abs(ActionNow->GetCustomSize().x) / 2||
                    GetCurrentPosition().x < -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2) {
                    ActionNow->m_Transform.translation.x = std::clamp(GetCurrentPosition().x,
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
        if (PushboxIsCollidedEnemy()) {
            glm::vec2 myPos = GetCurrentPosition() + GetCurrentPushboxOffset();
            glm::vec2 enemyPos = enemy->GetCurrentPosition() + enemy->GetCurrentPushboxOffset();
            glm::vec2 myPushboxSize = GetCurrentPushbox();
            glm::vec2 enemyPushboxSize = enemy->GetCurrentPushbox();

            float enemyLeft = enemyPos.x - enemyPushboxSize.x / 2;
            float enemyRight = enemyPos.x + enemyPushboxSize.x / 2;

            if (myPos.x <= enemyPos.x) {
                ActionNow->m_Transform.translation.x = std::max(enemyLeft - myPushboxSize.x / 2, -MaxWidth + myPushboxSize.x / 2)-GetCurrentPushboxOffset().x;
                if(enemy->currentState==FighterState::Idle||enemy->currentState==FighterState::Crouchdown||enemy->currentState==FighterState::JumpUP||
                    enemy->currentState==FighterState::JumpForward||enemy->currentState==FighterState::Backward) {
                    enemy->ActionNow->m_Transform.translation.x+=400*Time::GetDeltaTimeMs()/1000;
                }
            } else {
                ActionNow->m_Transform.translation.x = std::min(enemyRight + myPushboxSize.x / 2, MaxWidth - myPushboxSize.x / 2)-GetCurrentPushboxOffset().x;
                if(enemy->currentState==FighterState::Idle||enemy->currentState==FighterState::Crouchdown||enemy->currentState==FighterState::JumpUP||
                    enemy->currentState==FighterState::JumpForward||enemy->currentState==FighterState::Backward) {
                    enemy->ActionNow->m_Transform.translation.x+=-400*Time::GetDeltaTimeMs()/1000;
                    }
            }
        }
    }

    int Fighter::GetDirection() {
        if(GetCurrentPosition().x+GetCurrentPushbox().x+GetCurrentPushboxOffset().x
            <=enemy->GetCurrentPosition().x+enemy->GetCurrentPushboxOffset().x) {
            return static_cast<int>(FighterDirection::Left);
        }
        else if(GetCurrentPosition().x+GetCurrentPushboxOffset().x
            >=enemy->GetCurrentPosition().x+enemy->GetCurrentPushbox().x+enemy->GetCurrentPushboxOffset().x) {
            return static_cast<int>(FighterDirection::Right);
        }
        return direction;
    }

    void Fighter::UploadStateAndNewXY() {
        auto currentEnter = StateUpload.find(currentState);
        currentEnter->second();

        glm::vec2 position={ActionNow->GetTransform().translation.x+velocity.x*Time::GetDeltaTimeMs()/1000,
            ActionNow->GetTransform().translation.y+velocity.y*Time::GetDeltaTimeMs()/1000};
        ActionNow->SetTransform({position,0,{direction,1}});
    }

    void Fighter::HitboxIsCollidedEnemy() {
        if(GetCurrentHitboxOffset()==glm::vec2{-1,-1}||AttackStruck==true){return;}
        auto enemyPos = enemy->GetCurrentOffsetPosition();
        auto bodyOffsets = enemy->GetCurrentHurtboxOffset();
        auto bodySizes = enemy->GetCurrentHurtboxSize();

        for (size_t i = 0; i < bodyOffsets.size(); i++) {
            auto& BodyOffset = bodyOffsets[i];
            auto& BodySize = bodySizes[i];
            if(RectangleOverlap(
                GetCurrentOffsetPosition()+GetCurrentHitboxOffset(),
                GetCurrentHitbox(),
                enemyPos+BodyOffset,
                BodySize))
                {
                std::cout<<GetName()<<"HIT"<<i<<std::endl;
                enemy->hp-=GetAttack();
                AttackStruck=true;
                return;
            }
        }
    }
    //debug
    void Fighter::debugInit() {
        pushboxPicture=std::make_shared<AnimationSpace>(std::vector<std::string> {RESOURCE_DIR"/EditMaterial/pushbox.png"},
        true,120,true,6);
        headPicture=std::make_shared<AnimationSpace>(std::vector<std::string> {RESOURCE_DIR"/EditMaterial/head.png"},
        true,120,true,7);
        bodyPicture=std::make_shared<AnimationSpace>(std::vector<std::string> {RESOURCE_DIR"/EditMaterial/body.png"},
        true,120,true,8);
        legPicture=std::make_shared<AnimationSpace>(std::vector<std::string> {RESOURCE_DIR"/EditMaterial/leg.png"},
        true,120,true,9);
        hitPicture=std::make_shared<AnimationSpace>(std::vector<std::string> {RESOURCE_DIR"/EditMaterial/hitbox.png"},
        true,120,true,10);
    }

    void Fighter::PrintPostion() {
        if(Allofmouse.size()==animations[currentState].size()&&!Allofmouse.empty()) {
            std::cout<<"{";
            for(auto i: Allofmouse) {
                if(i==Allofmouse[Allofmouse.size()-1]) {
                    std::cout <<"{"<< static_cast<int> (i.x)<<","<< static_cast<int> (i.y)<<"}";
                }
                else {
                    std::cout <<"{"<< static_cast<int> (i.x)<<","<< static_cast<int> (i.y)<<"},";
                }
            }
            std::cout <<"};"<< std::endl;
        }
    }

    void Fighter::PostionTester() {
        if (Input::IsKeyDown(Keycode::MOUSE_MB)) {
            mouse = Input::GetCursorPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << mouse.x << ", " << mouse.y << ")" << std::endl;
            Allofmouse.clear();
        }
        if (Input::IsKeyDown(Keycode::B)) {
            mouse = GetCurrentOffsetPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << mouse.x << ", " << mouse.y << ")" << std::endl;
            Allofmouse.clear();
        }
        if (Input::IsKeyDown(Keycode::MOUSE_RB)) {
            glm::vec2 Mouse=Input::GetCursorPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << Mouse.x << ", " << Mouse.y << ")" << std::endl;
            glm::vec2 Pos=mouse-Mouse;
            Allofmouse.push_back(Pos);
        }
        if (Input::IsKeyDown(Keycode::N)) {
            glm::vec2 Mouse=Input::GetCursorPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << Mouse.x << ", " << Mouse.y << ")" << std::endl;
            glm::vec2 Pos;
            if(Mouse.y>mouse.y) {
                Pos=Mouse-mouse;
            }
            else {
                Pos=mouse-Mouse;
            }
            Allofmouse.push_back(Pos);
        }
    }

    void Fighter::PushBoxTester() {
        if(Input::IsKeyDown(Keycode::O)) {
            pushboxPicture->SetVisible(true);
        }
        if(Input::IsKeyDown(Keycode::P)) {
            pushboxPicture->SetVisible(false);
        }
        if(Input::IsKeyDown(Keycode::K)) {
            headPicture->SetVisible(true);
            bodyPicture->SetVisible(true);
            legPicture->SetVisible(true);
        }
        if(Input::IsKeyDown(Keycode::L)) {
            headPicture->SetVisible(false);
            bodyPicture->SetVisible(false);
            legPicture->SetVisible(false);
        }
    }

    void Fighter::Upload(std::shared_ptr<Core::Context> context) {
        PostionTester();
        PushBoxTester();
        PrintPostion();

        UploadStateAndNewXY();
        ReSize();
        BorderDetection(context->GetWindowWidth()/2);
        HitboxIsCollidedEnemy();
        //debug
        pushboxPicture->SetDrawData({GetCurrentPosition()+GetCurrentPushboxOffset(), 0, {direction, 1}},
                       GetCurrentPushbox(),
                       4.0f);
        headPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[0], 0, {direction, 1}},
                       GetCurrentHurtboxSize()[0],
                       5.0f);
        bodyPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[1], 0, {direction, 1}},
                       GetCurrentHurtboxSize()[1],
                       6.0f);
        legPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[2], 0, {direction, 1}},
                       GetCurrentHurtboxSize()[2],
                       7.0f);
        hitPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHitboxOffset(), 0, {direction, 1}},
               GetCurrentHitbox(),
               7.0f);
    }

    void Fighter::DrawCharacter() {
        ActionNow->custom_Draw();

        pushboxPicture->custom_Draw();
        headPicture->custom_Draw();
        bodyPicture->custom_Draw();
        legPicture->custom_Draw();
        if(GetCurrentHitboxOffset()!=glm::vec2{-1,-1}) {
            hitPicture->custom_Draw();
        }
    }
    //Actions
    void Fighter::IdleStateEnter(){
        ResetVelocity();
        AttackStruck=false;
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::IdleStateUpload() {
        if (GetAnimationIsEnd()) {ActionNow->AnimationPlay();}
        else if (controller->IsForward(direction)) {ChangeState(FighterState::Forward);}
        else if (controller->IsBackward(direction)) {ChangeState(FighterState::Backward);}
        else if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::Crouchdown);}
        else if (controller->IsKeyDown(Keys::UP)) {ChangeState(FighterState::JumpUP);}
        else if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::LP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::MP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::HP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::LK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::MK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::HK);}
        direction=GetDirection();
    }

    void Fighter::WalkStateEnter(){
        velocity.x=direction*Initialvelocity.x[currentState];
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::ForwardStateUpload() {
        if (GetAnimationIsEnd()) {ActionNow->AnimationPlay();}
        if (!controller->IsForward(direction)) {ChangeState(FighterState::Idle);}
        if (controller->IsKeyDown(Keys::UP)) {ChangeState(FighterState::JumpForward);}
        if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::Crouchdown);}
        if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::LP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::MP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::HP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::LK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::MK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::HK);}
        direction=GetDirection();
    }
    void Fighter::BackwardStateUpload() {
        if (GetAnimationIsEnd()) {ActionNow->AnimationPlay();}
        if (!controller->IsBackward(direction)) {ChangeState(FighterState::Idle);}
        if (controller->IsKeyDown(Keys::UP)) {ChangeState(FighterState::JumpBackward);}
        if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::Crouchdown);}
        if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::LP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::MP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::HP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::LK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::MK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::HK);}
        direction=GetDirection();
    }

    void Fighter::JumpStateEnter(){
        velocity.x=direction*Initialvelocity.x[currentState];
        velocity.y=Initialvelocity.y[currentState];
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::JumpStateUpload(){
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
        direction=GetDirection();
    }

    void Fighter::CrouchdownEnter(){
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::CrouchdownUpload() {
        if (!controller->IsKeyPressed(Keys::DOWN)){ChangeState(FighterState::Idle);}
        direction=GetDirection();
    }

    void Fighter::AttackStateEnter() {
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::LPStateUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::MPStateUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::HPStateUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::LKStateUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::MKStateUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::HKStateUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

}