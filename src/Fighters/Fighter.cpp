#include "Fighters/Fighter.hpp"
namespace Util {
    void Fighter::LoadAttackAndType() {
        attacks[FighterState::LP]=attacks[FighterState::LK]=attacks[FighterState::CrouchLP]=attacks[FighterState::CrouchLK]=5;
        attacks[FighterState::MP]=attacks[FighterState::MK]=attacks[FighterState::CrouchMP]=attacks[FighterState::CrouchMK]=10;
        attacks[FighterState::HP]=attacks[FighterState::HK]=attacks[FighterState::CrouchHP]=attacks[FighterState::CrouchHK]=15;

        hitstrength[FighterState::LP]=hitstrength[FighterState::LK]=hitstrength[FighterState::CrouchLP]=hitstrength[FighterState::CrouchLK]=HitStrength::L;
        hitstrength[FighterState::MP]=hitstrength[FighterState::MK]=hitstrength[FighterState::CrouchMP]=hitstrength[FighterState::CrouchMK]=HitStrength::M;
        hitstrength[FighterState::HP]=hitstrength[FighterState::HK]=hitstrength[FighterState::CrouchHP]=hitstrength[FighterState::CrouchHK]=HitStrength::H;
    }
    void Fighter::LoadAttackSound() {
        soundeffect[FighterState::LP]=soundeffect[FighterState::LK]=soundeffect[FighterState::CrouchLP]=soundeffect[FighterState::CrouchLK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_38 - Light Attack.wav")};
        soundeffect[FighterState::MP]=soundeffect[FighterState::MK]=soundeffect[FighterState::CrouchMP]=soundeffect[FighterState::CrouchMK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_39 - Medium Attack.wav")};
        soundeffect[FighterState::HP]=soundeffect[FighterState::HK]=soundeffect[FighterState::CrouchHP]=soundeffect[FighterState::CrouchHK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_40 - Hard Attack.wav")};
        soundeffect[FighterState::HurtBodyL]=soundeffect[FighterState::HurtHeadL]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_42 - Jab Hit.wav")};
        soundeffect[FighterState::HurtBodyM]=soundeffect[FighterState::HurtHeadM]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_43 - Strong Hit.wav")};
        soundeffect[FighterState::HurtBodyH]=soundeffect[FighterState::HurtHeadH]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_44 - Fierce Hit.wav")};
        soundeffect[FighterState::BackwardBlock]=soundeffect[FighterState::CrouchBlock]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_51 - Blocked.wav")};
    }
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
        borderCheckStates = {
            FighterState::Idle, FighterState::Forward, FighterState::Backward,
            FighterState::JumpUP, FighterState::JumpForward, FighterState::JumpBackward,
            FighterState::Crouch,FighterState::CrouchDown,FighterState::CrouchUp,
            FighterState::HurtBodyL, FighterState::HurtBodyM, FighterState::HurtBodyH,
            FighterState::HurtHeadL, FighterState::HurtHeadM, FighterState::HurtHeadH,
            FighterState::BackwardBlock,FighterState::CrouchBlock
        };
        CrouchAttackStates={
            FighterState::CrouchLP, FighterState::CrouchMP,FighterState::CrouchHP,
            FighterState::CrouchLK,FighterState::CrouchMK, FighterState::CrouchHK
        };
        HurtStates={
            FighterState::HurtBodyL, FighterState::HurtBodyM, FighterState::HurtBodyH,
            FighterState::HurtHeadL, FighterState::HurtHeadM, FighterState::HurtHeadH
        };
        StateEnter[FighterState::Idle] = [this] { IdleStateEnter(); };
        StateEnter[FighterState::Forward] = [this] { WalkStateEnter(); };
        StateEnter[FighterState::Backward] = [this] { WalkStateEnter(); };
        StateEnter[FighterState::JumpUP] = [this] { JumpStateEnter(); };
        StateEnter[FighterState::JumpForward] = [this] { JumpStateEnter(); };
        StateEnter[FighterState::JumpBackward] = [this] { JumpStateEnter(); };
        StateEnter[FighterState::Crouch] = [this] { CrouchEnter(); };
        StateEnter[FighterState::CrouchDown] = [this] { CrouchEnter(); };
        StateEnter[FighterState::CrouchUp] = [this] { CrouchEnter(); };

        StateEnter[FighterState::LP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::MP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::HP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::LK] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::MK] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::HK] = [this] { AttackStateEnter(); };

        StateEnter[FighterState::CrouchLP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::CrouchMP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::CrouchHP] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::CrouchLK] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::CrouchMK] = [this] { AttackStateEnter(); };
        StateEnter[FighterState::CrouchHK] = [this] { AttackStateEnter(); };

        StateEnter[FighterState::HurtHeadL] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtHeadM] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtHeadH] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtBodyL] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtBodyM] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtBodyH] = [this] { HurtStateEnter(); };

        StateEnter[FighterState::BackwardBlock] = [this] { BlockStateEnter(); };
        StateEnter[FighterState::CrouchBlock] = [this] { BlockStateEnter(); };

        StateUpload[FighterState::Idle] = [this] { IdleStateUpload(); };
        StateUpload[FighterState::Forward] = [this] { ForwardStateUpload(); };
        StateUpload[FighterState::Backward] = [this] { BackwardStateUpload(); };
        StateUpload[FighterState::JumpUP] = [this] { JumpStateUpload(); };
        StateUpload[FighterState::JumpForward] = [this] { JumpStateUpload(); };
        StateUpload[FighterState::JumpBackward] = [this] { JumpStateUpload(); };
        StateUpload[FighterState::Crouch] = [this] { CrouchUpload(); };
        StateUpload[FighterState::CrouchDown] = [this] { CrouchDownUpload(); };
        StateUpload[FighterState::CrouchUp] = [this] { CrouchUpUpload(); };

        StateUpload[FighterState::LP] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::MP] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::HP] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::LK] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::MK] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::HK] = [this] {AttackStateUpload(); };

        StateUpload[FighterState::CrouchLP] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::CrouchMP] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::CrouchHP] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::CrouchLK] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::CrouchMK] = [this] {AttackStateUpload(); };
        StateUpload[FighterState::CrouchHK] = [this] {AttackStateUpload(); };

        StateUpload[FighterState::HurtHeadL] = [this] { HurtStateUpload(); };
        StateUpload[FighterState::HurtHeadM] = [this] { HurtStateUpload(); };
        StateUpload[FighterState::HurtHeadH] = [this] { HurtStateUpload(); };
        StateUpload[FighterState::HurtBodyL] = [this] { HurtStateUpload(); };
        StateUpload[FighterState::HurtBodyM] = [this] { HurtStateUpload(); };
        StateUpload[FighterState::HurtBodyH] = [this] { HurtStateUpload(); };

        StateUpload[FighterState::BackwardBlock] = [this] { BlockStateUpload(); };
        StateUpload[FighterState::CrouchBlock] = [this] { BlockStateUpload(); };
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
        FloorOfCharacter=ActionNow->GetOriginalSize().y * 3/2 + position.y;
        ActionNow->SetDrawData({{position.x,FloorOfCharacter}, 0, {side, 1}},
                               ActionNow->GetOriginalSize()*glm::vec2 {3,3},
                               2.0f);
        direction = side;
        ChangeState(FighterState::Idle);
        ActionNow->SetLooping(true);
        controller->SetPlayerController(Whichplayer);

        pushboxPicture->SetDrawData({GetCurrentPosition(), 0, {1, 1}},GetCurrentPushbox(),4.0f);
        pushboxPicture->SetVisible(false);
        headPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[0], 0, {1, 1}},GetCurrentHurtboxSize()[0],5.0f);
        headPicture->SetVisible(false);
        bodyPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[1], 0, {1, 1}},GetCurrentHurtboxSize()[1],6.0f);
        bodyPicture->SetVisible(false);
        legPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHurtboxOffset()[2], 0, {1, 1}},GetCurrentHurtboxSize()[2],7.0f);
        legPicture->SetVisible(false);
        hitPicture->SetDrawData({GetCurrentOffsetPosition()+GetCurrentHitboxOffset(), 0, {1, 1}},GetCurrentHitbox(),8.0f);
        hitPicture->SetVisible(false);
    }

    void Fighter::ReSize() {
        if (!ActionNow) return;
        ActionNow->SetDrawData(
            {ActionNow->m_Transform.translation, 0, {direction, 1}},
            ActionNow->GetOriginalSize()*glm::vec2 {3,3},
            2.0f
        );
    }

    void Fighter::BorderDetection(int MaxWidth) {
        if (borderCheckStates.count(currentState)) {
            if (GetCurrentPosition().x > MaxWidth - abs(ActionNow->GetCustomSize().x) / 2||
                GetCurrentPosition().x < -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2) {
                ActionNow->m_Transform.translation.x = std::clamp(GetCurrentPosition().x,
                    -MaxWidth + abs(ActionNow->GetCustomSize().x) / 2,
                    MaxWidth - abs(ActionNow->GetCustomSize().x)  / 2);
                }
            if (ActionNow->m_Transform.translation.y < FloorOfCharacter) {
                ActionNow->m_Transform.translation.y=FloorOfCharacter;
            }
        }
        if (PushboxIsCollidedEnemy()&&!HurtStates.count(currentState)) {
            glm::vec2 myPos = GetCurrentPosition() + GetCurrentPushboxOffset();
            glm::vec2 enemyPos = enemy->GetCurrentPosition() + enemy->GetCurrentPushboxOffset();
            glm::vec2 myPushboxSize = GetCurrentPushbox();
            glm::vec2 enemyPushboxSize = enemy->GetCurrentPushbox();

            float enemyLeft = enemyPos.x - enemyPushboxSize.x / 2;
            float enemyRight = enemyPos.x + enemyPushboxSize.x / 2;

            if (myPos.x <= enemyPos.x) {
                ActionNow->m_Transform.translation.x = std::max(enemyLeft - myPushboxSize.x / 2, -MaxWidth + myPushboxSize.x / 2)-GetCurrentPushboxOffset().x;
                if(enemy->currentState==FighterState::Idle||enemy->currentState==FighterState::Crouch||enemy->currentState==FighterState::JumpUP||
                    enemy->currentState==FighterState::JumpForward||enemy->currentState==FighterState::Backward) {
                    enemy->ActionNow->m_Transform.translation.x+=400*Time::GetDeltaTimeMs()/1000;
                }
            } else {
                ActionNow->m_Transform.translation.x = std::min(enemyRight + myPushboxSize.x / 2, MaxWidth - myPushboxSize.x / 2)-GetCurrentPushboxOffset().x;
                if(enemy->currentState==FighterState::Idle||enemy->currentState==FighterState::Crouch||enemy->currentState==FighterState::JumpUP||
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

        glm::vec2 position={ActionNow->GetTransform().translation.x+direction*velocity.x,
            ActionNow->GetTransform().translation.y+velocity.y};
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
                std::cout<<GetName()<<"HIT"<<i<<"||"<<enemy->IsBlocking()<<std::endl;
                if(enemy->IsBlocking()) {
                    enemy->AttackBlock();
                }
                else {
                    enemy->GetAttack();
                    AttackHit(GetHitStrength(),static_cast<HitLocation>(i));
                }
                AttackStruck=true;
                return;
            }
        }
    }

    void Fighter::AttackBlock() {
        FighterState newState=GetBlockState();
        ChangeState(newState);
    }

    void Fighter::AttackHit(HitStrength Strength,HitLocation Location) {
        FighterState newState=GetBeHitState(Strength,Location);
        enemy->ChangeState(newState);
    }

    bool Fighter::IsBlocking() {
        if(currentState==FighterState::Backward||currentState==FighterState::Crouch
            ||currentState==FighterState::Idle||currentState==FighterState::BackwardBlock
            ||currentState==FighterState::CrouchBlock) {
            return controller->IsBackward(direction);
        }
        return false;
    }

    FighterState Fighter::GetBeHitState(HitStrength Strength,HitLocation Location) {
        switch (Strength) {
            case HitStrength::L:
                if(Location==HitLocation::Head)return FighterState::HurtHeadL;
                return FighterState::HurtBodyL;
                break;
            case HitStrength::M:
                if(Location==HitLocation::Head)return FighterState::HurtHeadM;
                return FighterState::HurtBodyM;
                break;
            case HitStrength::H:
                if(Location==HitLocation::Head)return FighterState::HurtHeadH;
                return FighterState::HurtBodyH;
                break;
            default:
                return FighterState::Idle;
        }
    }

    FighterState Fighter::GetBlockState() {
        switch (currentState) {
            case FighterState::Backward:
                return FighterState::BackwardBlock;
            break;
            case FighterState::Crouch:
                return FighterState::CrouchBlock;
            break;
            default:
                return FighterState::Idle;
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
            std::cout<<GetName()<<"{";
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
        if (Input::IsKeyDown(Keycode::NUM_1)) {
            ChangeState(FighterState::Special_1);
        }
        if (Input::IsKeyDown(Keycode::NUM_2)) {
            ChangeState(FighterState::CrouchMP);
        }
        if (Input::IsKeyDown(Keycode::NUM_3)) {
            ChangeState(FighterState::CrouchHP);
        }
        if (Input::IsKeyDown(Keycode::NUM_4)) {
            ChangeState(FighterState::CrouchLK);
        }
        if (Input::IsKeyDown(Keycode::NUM_5)) {
            ChangeState(FighterState::CrouchMK);
        }
        if (Input::IsKeyDown(Keycode::NUM_6)) {
            ChangeState(FighterState::CrouchHK);
        }
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

        if (Input::IsKeyDown(Keycode::N)) {
            glm::vec2 Mouse=Input::GetCursorPosition();
            mouse=GetCurrentOffsetPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << Mouse.x << ", " << Mouse.y << ")" << std::endl;
            glm::vec2 Pos;
            Pos=Mouse-mouse;
            Allofmouse.push_back(Pos);
        }
        if (Input::IsKeyDown(Keycode::MOUSE_RB)) {
            glm::vec2 Mouse=Input::GetCursorPosition();
            std::cout << "Frame: " << "Mouse Clicked at: (" << Mouse.x << ", " << Mouse.y << ")" << std::endl;
            glm::vec2 Pos;
            Pos=mouse-Mouse;
            Allofmouse.push_back(Pos);
        }
    }

    void Fighter::PushBoxTester() {
        if(Input::IsKeyDown(Keycode::I)) {
            pushboxPicture->SetVisible(!pushboxPicture->GetVisible());
        }
        if(Input::IsKeyDown(Keycode::O)) {
            headPicture->SetVisible(!headPicture->GetVisible());
            bodyPicture->SetVisible(!bodyPicture->GetVisible());
            legPicture->SetVisible(!legPicture->GetVisible());
        }
        if(Input::IsKeyDown(Keycode::P)) {
            hitPicture->SetVisible(!hitPicture->GetVisible());
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
               8.0f);
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
        else if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::Crouch);}
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
        velocity.x=Initialvelocity.x[currentState];
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::ForwardStateUpload() {
        if (GetAnimationIsEnd()) {ActionNow->AnimationPlay();}
        if (!controller->IsForward(direction)) {ChangeState(FighterState::Idle);}
        if (controller->IsKeyDown(Keys::UP)) {ChangeState(FighterState::JumpForward);}
        if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::Crouch);}
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
        if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::CrouchDown);}
        if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::LP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::MP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::HP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::LK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::MK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::HK);}
        direction=GetDirection();
    }

    void Fighter::JumpStateEnter(){
        velocity.x=Initialvelocity.x[currentState];
        velocity.y=Initialvelocity.y[currentState];
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::JumpStateUpload(){
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::CrouchEnter(){
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::CrouchUpload() {
        if (!controller->IsKeyPressed(Keys::DOWN)){ChangeState(FighterState::CrouchUp);}
        if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::CrouchLP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::CrouchMP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::CrouchHP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::CrouchLK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::CrouchMK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::CrouchHK);}
        direction=GetDirection();
    }
    void Fighter::CrouchDownUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Crouch);}
    }
    void Fighter::CrouchUpUpload() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::AttackStateEnter() {
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        soundeffect[currentState]->Play();
    }
    void Fighter::AttackStateUpload() {
        if (GetAnimationIsEnd()&&CrouchAttackStates.count(currentState)) {ChangeState(FighterState::Crouch);}
        else if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::HurtStateEnter() {
        ResetVelocity();
        velocity.x=Initialvelocity.x[currentState];
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        soundeffect[currentState]->Play();
    }
    void Fighter::HurtStateUpload() {
        velocity.x+=Friction*Time::GetDeltaTimeMs()/1000;
        velocity.y+=Gravity*Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()&&velocity.x>=0) {ChangeState(FighterState::Idle);}
    }
    void Fighter::BlockStateEnter() {
        ResetVelocity();
        velocity.x=Initialvelocity.x[currentState];
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        soundeffect[currentState]->Play();
    }
    void Fighter::BlockStateUpload() {
        velocity.x+=Friction/2*Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()&&velocity.x>=0&&currentState==FighterState::CrouchBlock) {ChangeState(FighterState::Crouch);}
        else if (GetAnimationIsEnd()&&velocity.x>=0&&currentState==FighterState::BackwardBlock) {ChangeState(FighterState::Idle);}
    }
}