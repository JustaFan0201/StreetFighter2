#include "Fighters/Fighter.hpp"
namespace Util {
    void Fighter::LoadCommonVelocities() {
        Initialvelocity.x[FighterState::Forward]=8;
        Initialvelocity.x[FighterState::Backward]=-8;
        Initialvelocity.x[FighterState::JumpForward]=10;
        Initialvelocity.x[FighterState::JumpBackward]=-10;
        Initialvelocity.y[FighterState::JumpForward]=38;
        Initialvelocity.y[FighterState::JumpBackward]=38;
        Initialvelocity.y[FighterState::JumpUP]=38;

        Initialvelocity.x[FighterState::HurtBodyL]=Initialvelocity.x[FighterState::HurtHeadL]=-7;
        Initialvelocity.x[FighterState::HurtBodyM]=Initialvelocity.x[FighterState::HurtHeadM]=-8;
        Initialvelocity.x[FighterState::HurtBodyH]=Initialvelocity.x[FighterState::HurtHeadH]=-10;

        Initialvelocity.x[FighterState::KnockDownL]=-12;
        Initialvelocity.x[FighterState::KnockDownM]=-14;
        Initialvelocity.x[FighterState::KnockDownH]=-16;
        Initialvelocity.y[FighterState::KnockDownL]=20;
        Initialvelocity.y[FighterState::KnockDownM]=24;
        Initialvelocity.y[FighterState::KnockDownH]=28;

        Initialvelocity.x[FighterState::BackwardBlock]=Initialvelocity.x[FighterState::CrouchBlock]=-4;
        Initialvelocity.x[FighterState::DefeatedLoss]=-10;
        Initialvelocity.y[FighterState::DefeatedLoss]=35;
    }
    void Fighter::LoadAttackAndType() {
        attacks[FighterState::LP]=attacks[FighterState::LK]=attacks[FighterState::CrouchLP]=attacks[FighterState::CrouchLK]=5;
        attacks[FighterState::MP]=attacks[FighterState::MK]=attacks[FighterState::CrouchMP]=attacks[FighterState::CrouchMK]=10;
        attacks[FighterState::HP]=attacks[FighterState::HK]=attacks[FighterState::CrouchHP]=attacks[FighterState::CrouchHK]=15;
        attacks[FighterState::JumpLP]=attacks[FighterState::JumpLK]=5;
        attacks[FighterState::JumpMP]=attacks[FighterState::JumpMK]=10;
        attacks[FighterState::JumpHP]=attacks[FighterState::JumpHK]=15;

        hitstrength[FighterState::LP]=hitstrength[FighterState::LK]=hitstrength[FighterState::CrouchLP]=hitstrength[FighterState::CrouchLK]=HitStrength::L;
        hitstrength[FighterState::MP]=hitstrength[FighterState::MK]=hitstrength[FighterState::CrouchMP]=hitstrength[FighterState::CrouchMK]=HitStrength::M;
        hitstrength[FighterState::HP]=hitstrength[FighterState::HK]=hitstrength[FighterState::CrouchHP]=hitstrength[FighterState::CrouchHK]=HitStrength::H;

        hitstrength[FighterState::JumpLP]=hitstrength[FighterState::JumpLK]=HitStrength::L;
        hitstrength[FighterState::JumpMP]=hitstrength[FighterState::JumpMK]=HitStrength::M;
        hitstrength[FighterState::JumpHP]=hitstrength[FighterState::JumpHK]=HitStrength::H;

        attacktype[FighterState::JumpLP]=attacktype[FighterState::JumpLK]=AttackType::Upper;
        attacktype[FighterState::JumpMP]=attacktype[FighterState::JumpMK]=AttackType::Upper;
        attacktype[FighterState::JumpHP]=attacktype[FighterState::JumpHK]=AttackType::Upper;
    }
    void Fighter::LoadAttackSound() {
        soundeffect[FighterState::LP]=soundeffect[FighterState::LK]=soundeffect[FighterState::CrouchLP]=soundeffect[FighterState::CrouchLK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_38 - Light Attack.wav")};
        soundeffect[FighterState::MP]=soundeffect[FighterState::MK]=soundeffect[FighterState::CrouchMP]=soundeffect[FighterState::CrouchMK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_39 - Medium Attack.wav")};
        soundeffect[FighterState::HP]=soundeffect[FighterState::HK]=soundeffect[FighterState::CrouchHP]=soundeffect[FighterState::CrouchHK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_40 - Hard Attack.wav")};
        soundeffect[FighterState::KnockDownL]=soundeffect[FighterState::HurtBodyL]=soundeffect[FighterState::HurtHeadL]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_42 - Jab Hit.wav")};
        soundeffect[FighterState::KnockDownM]=soundeffect[FighterState::HurtBodyM]=soundeffect[FighterState::HurtHeadM]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_43 - Strong Hit.wav")};
        soundeffect[FighterState::KnockDownH]=soundeffect[FighterState::HurtBodyH]=soundeffect[FighterState::HurtHeadH]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_44 - Fierce Hit.wav")};
        soundeffect[FighterState::BackwardBlock]=soundeffect[FighterState::CrouchBlock]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_51 - Blocked.wav")};
    }

    void Fighter::LoadCurrentSpecialMove(Keys ButtonType) {
        Keys fallbackKey = (SpecialMoveData.SkillCommand[currentState].requiredAttack == AttackButton::ANY_PUNCH||
                            SpecialMoveData.SkillCommand[currentState].requiredAttack == AttackButton::ALL_PUNCH)
                            ? Keys::LP : Keys::LK;

        auto& anim = SpecialMoveData.animationData[currentState];
        auto& atk = SpecialMoveData.attackdata[currentState];
        auto& sound = SpecialMoveData.sounddata[currentState];

        // Frames
        if (anim.frames.count(ButtonType)) {
            frames[currentState] = anim.frames[ButtonType];
        } else {
            frames[currentState] = anim.frames[fallbackKey];
        }

        // Velocity
        if (anim.velocitys.count(ButtonType)) {
            velocity = anim.velocitys[ButtonType];
        }

        // Initial Velocity
        if (anim.initialvelocitys.count(ButtonType)) {
            Initialvelocity.x[currentState] = anim.initialvelocitys[ButtonType].x;
            Initialvelocity.y[currentState] = anim.initialvelocitys[ButtonType].y;
        }
        else if(anim.initialvelocitys.count(fallbackKey)){
            Initialvelocity.x[currentState] = anim.initialvelocitys[fallbackKey].x;
            Initialvelocity.y[currentState] = anim.initialvelocitys[fallbackKey].y;
        }

        // Attack Info
        if (atk.attack.count(ButtonType)) {
            attacks[currentState] = atk.attack[ButtonType];
        }
        else {
            attacks[currentState] = atk.attack[fallbackKey];
        }
        if (atk.HitStrength.count(ButtonType)) {
            hitstrength[currentState] = atk.HitStrength[ButtonType];
        }
        else {
            hitstrength[currentState] = atk.HitStrength[fallbackKey];
        }
        //sound
        if(sound.sound.count(ButtonType)) {
            soundeffect[currentState] = sound.sound[ButtonType];
        }
        else {
            soundeffect[currentState] = sound.sound[fallbackKey];
        }
    }

    void Fighter::ChangeState(FighterState newState) {
        if (currentState != newState||SpecificStates.HurtStates.count(newState)) {
            currentState = newState;
            auto currentEnter = StateEnter.find(currentState);
            if (currentEnter != StateEnter.end()) {
                currentEnter->second();
            }
            AttackStruck=false;
            HitEnemy=false;
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
        SpecificStates.borderCheckStates = {
            FighterState::Idle, FighterState::Forward, FighterState::Backward,
            FighterState::JumpUP, FighterState::JumpForward, FighterState::JumpBackward,
            FighterState::Crouch,FighterState::CrouchDown,FighterState::CrouchUp,
            FighterState::HurtBodyL, FighterState::HurtBodyM, FighterState::HurtBodyH,
            FighterState::HurtHeadL, FighterState::HurtHeadM, FighterState::HurtHeadH,
            FighterState::KnockDownL, FighterState::KnockDownM, FighterState::KnockDownH,FighterState::GetUp,
            FighterState::JumpLP, FighterState::JumpMP, FighterState::JumpHP,
            FighterState::JumpLK, FighterState::JumpMK, FighterState::JumpHK,
            FighterState::JumpAttackEnd,
            FighterState::BackwardBlock,FighterState::CrouchBlock,
            FighterState::DefeatedLoss,FighterState::TimeOverLoss
        };
        SpecificStates.CrouchAttackStates={
            FighterState::CrouchLP, FighterState::CrouchMP,FighterState::CrouchHP,
            FighterState::CrouchLK,FighterState::CrouchMK, FighterState::CrouchHK
        };
        SpecificStates.HurtStates={
            FighterState::HurtBodyL, FighterState::HurtBodyM, FighterState::HurtBodyH,
            FighterState::HurtHeadL, FighterState::HurtHeadM, FighterState::HurtHeadH
        };
        SpecificStates.BlockStates={
            FighterState::BackwardBlock, FighterState::CrouchBlock
        };
        SpecificStates.CanBlockStates={
            FighterState::Idle,FighterState::Forward,
            FighterState::Backward, FighterState::Crouch,
            FighterState::CrouchDown,FighterState::CrouchUp,
            FighterState::BackwardBlock, FighterState::CrouchBlock
        };
        SpecificStates.SpecialStates={
            FighterState::Special_1, FighterState::Special_2, FighterState::Special_3
        };
        SpecificStates.IdleStates={
            FighterState::Idle, FighterState::Forward, FighterState::Backward,
            FighterState::Crouch,FighterState::CrouchDown,FighterState::CrouchUp
        };
        SpecificStates.StandStates={
            FighterState::Idle, FighterState::Forward, FighterState::Backward, FighterState::BackwardBlock
        };
        SpecificStates.CrouchStates={
            FighterState::Crouch,FighterState::CrouchDown,FighterState::CrouchUp, FighterState::CrouchBlock
        };
        SpecificStates.Invincible={
            FighterState::KnockDownL, FighterState::KnockDownM, FighterState::KnockDownH,FighterState::GetUp,
            FighterState::Win, FighterState::WinStart, FighterState::TimeOverLoss,
            FighterState::DefeatedLoss
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

        StateEnter[FighterState::JumpLP] = [this] { JumpAttackStateEnter(); };
        StateEnter[FighterState::JumpMP] = [this] { JumpAttackStateEnter(); };
        StateEnter[FighterState::JumpHP] = [this] { JumpAttackStateEnter(); };
        StateEnter[FighterState::JumpLK] = [this] { JumpAttackStateEnter(); };
        StateEnter[FighterState::JumpMK] = [this] { JumpAttackStateEnter(); };
        StateEnter[FighterState::JumpHK] = [this] { JumpAttackStateEnter(); };
        StateEnter[FighterState::JumpAttackEnd] = [this] { JumpAttackEndStateEnter(); };

        StateEnter[FighterState::HurtHeadL] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtHeadM] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtHeadH] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtBodyL] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtBodyM] = [this] { HurtStateEnter(); };
        StateEnter[FighterState::HurtBodyH] = [this] { HurtStateEnter(); };

        StateEnter[FighterState::KnockDownL] = [this] { KnockDownStateEnter(); };
        StateEnter[FighterState::KnockDownM] = [this] { KnockDownStateEnter(); };
        StateEnter[FighterState::KnockDownH] = [this] { KnockDownStateEnter(); };
        StateEnter[FighterState::GetUp] = [this] { GetUpStateEnter(); };

        StateEnter[FighterState::BackwardBlock] = [this] { BlockStateEnter(); };
        StateEnter[FighterState::CrouchBlock] = [this] { BlockStateEnter(); };

        StateEnter[FighterState::WinStart] = [this] { WinStateEnter(); };
        StateEnter[FighterState::Win] = [this] { WinStateEnter(); };

        StateEnter[FighterState::TimeOverLoss] = [this] { LossStateEnter(); };
        StateEnter[FighterState::DefeatedLoss] = [this] { LossStateEnter(); };

        StateUpdate[FighterState::Idle] = [this] {IdleStateUpdate(); };
        StateUpdate[FighterState::Forward] = [this] { ForwardStateUpdate(); };
        StateUpdate[FighterState::Backward] = [this] { BackwardStateUpdate(); };
        StateUpdate[FighterState::JumpUP] = [this] {JumpStateUpdate(); };
        StateUpdate[FighterState::JumpForward] = [this] {JumpStateUpdate(); };
        StateUpdate[FighterState::JumpBackward] = [this] { JumpStateUpdate(); };
        StateUpdate[FighterState::Crouch] = [this] {CrouchUpdate(); };
        StateUpdate[FighterState::CrouchDown] = [this] {CrouchDownUpdate(); };
        StateUpdate[FighterState::CrouchUp] = [this] {CrouchUpUpdate(); };

        StateUpdate[FighterState::LP] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::MP] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::HP] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::LK] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::MK] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::HK] = [this] {AttackStateUpdate(); };

        StateUpdate[FighterState::CrouchLP] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::CrouchMP] = [this] {AttackStateUpdate();};
        StateUpdate[FighterState::CrouchHP] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::CrouchLK] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::CrouchMK] = [this] {AttackStateUpdate(); };
        StateUpdate[FighterState::CrouchHK] = [this] {  AttackStateUpdate(); };

        StateUpdate[FighterState::JumpLP] = [this] {JumpAttackStateUpdate(); };
        StateUpdate[FighterState::JumpMP] = [this] {JumpAttackStateUpdate(); };
        StateUpdate[FighterState::JumpHP] = [this] {JumpAttackStateUpdate(); };
        StateUpdate[FighterState::JumpLK] = [this] {JumpAttackStateUpdate(); };
        StateUpdate[FighterState::JumpMK] = [this] {JumpAttackStateUpdate(); };
        StateUpdate[FighterState::JumpHK] = [this] {JumpAttackStateUpdate(); };
        StateUpdate[FighterState::JumpAttackEnd] = [this] {JumpAttackEndStateUpdate();};

        StateUpdate[FighterState::HurtHeadL] = [this] { HurtStateUpdate(); };
        StateUpdate[FighterState::HurtHeadM] = [this] { HurtStateUpdate(); };
        StateUpdate[FighterState::HurtHeadH] = [this] { HurtStateUpdate(); };
        StateUpdate[FighterState::HurtBodyL] = [this] { HurtStateUpdate(); };
        StateUpdate[FighterState::HurtBodyM] = [this] { HurtStateUpdate(); };
        StateUpdate[FighterState::HurtBodyH] = [this] { HurtStateUpdate(); };

        StateUpdate[FighterState::KnockDownL] = [this] { KnockDownStateUpdate(); };
        StateUpdate[FighterState::KnockDownM] = [this] { KnockDownStateUpdate(); };
        StateUpdate[FighterState::KnockDownH] = [this] { KnockDownStateUpdate(); };
        StateUpdate[FighterState::GetUp] = [this] { GetUpStateUpdate(); };

        StateUpdate[FighterState::BackwardBlock] = [this] {BlockStateUpdate(); };
        StateUpdate[FighterState::CrouchBlock] = [this] {BlockStateUpdate(); };

        StateUpdate[FighterState::WinStart] = [this] { WinStartStateUpdate(); };
        StateUpdate[FighterState::Win] = [this] { WinStateUpdate(); };

        StateUpdate[FighterState::TimeOverLoss] = [this] { LossStateUpdate(); };
        StateUpdate[FighterState::DefeatedLoss] = [this] { LossStateUpdate(); };
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

    void Fighter::InitPosition(glm::vec2 position, int side,std::shared_ptr<Controller> controller,int MaxCameraOffsetX) {
        if(FloorOfCharacter==0) {FloorOfCharacter=ActionNow->GetOriginalSize().y * 3/2 + position.y;}
        this->MaxCameraOffsetX=MaxCameraOffsetX;
        ActionNow->SetDrawData({{position.x,FloorOfCharacter}, 0, {side, 1}},
                               ActionNow->GetOriginalSize()*glm::vec2 {3,3},
                               2.0f);
        hp=100;
        direction = side;
        ChangeState(FighterState::Idle);
        this->controller=controller;

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

    void Fighter::BorderDetection(int MaxWidth, glm::vec2 cameraOffset) {
        this->MaxWidth = MaxWidth;
        currentCameraX=cameraOffset.x;
        const float clampEpsilon = 0.01f;

        if (SpecificStates.borderCheckStates.count(currentState)) {
            float halfFighterWidth = GetHalfFighterWidth();
            float worldX = GetCurrentPosition().x;
            float screenX = worldX - cameraOffset.x;

            float clampedScreenX = std::clamp(screenX, -MaxWidth + halfFighterWidth, MaxWidth - halfFighterWidth);
            float clampedWorldX = clampedScreenX + cameraOffset.x;

            if (std::abs(clampedScreenX - screenX) > clampEpsilon) {
                ActionNow->m_Transform.translation.x = clampedWorldX;
            }

            if (ActionNow->m_Transform.translation.y < FloorOfCharacter) {
                ActionNow->m_Transform.translation.y = FloorOfCharacter;
            }
        }

        if (PushboxIsCollidedEnemy() && !SpecificStates.HurtStates.count(currentState)) {
            glm::vec2 myPos = GetCurrentPosition() + GetCurrentPushboxOffset();
            glm::vec2 enemyPos = enemy->GetCurrentPosition() + enemy->GetCurrentPushboxOffset();
            glm::vec2 myPushboxSize = GetCurrentPushbox();
            glm::vec2 enemyPushboxSize = enemy->GetCurrentPushbox();

            float halfWindow = MaxWidth;

            float enemyLeft = enemyPos.x - enemyPushboxSize.x / 2;
            float enemyRight = enemyPos.x + enemyPushboxSize.x / 2;

            float worldLimitLeft = cameraOffset.x - halfWindow + myPushboxSize.x / 2;
            float worldLimitRight = cameraOffset.x + halfWindow - myPushboxSize.x / 2;

            if (myPos.x <= enemyPos.x) {
                float targetX = std::max(enemyLeft - myPushboxSize.x / 2, worldLimitLeft);
                ActionNow->m_Transform.translation.x = targetX - GetCurrentPushboxOffset().x;

                if (enemy->SpecificStates.IdleStates.count(enemy->currentState)) {
                    float pushSpeed = 400 * Time::GetDeltaTimeMs() / 1000.0f;
                    enemy->ActionNow->m_Transform.translation.x += pushSpeed;
                }
            }
            else {
                float targetX = std::min(enemyRight + myPushboxSize.x / 2, worldLimitRight);
                ActionNow->m_Transform.translation.x = targetX - GetCurrentPushboxOffset().x;

                if (enemy->SpecificStates.IdleStates.count(enemy->currentState)) {
                    float pushSpeed = 400 * Time::GetDeltaTimeMs() / 1000.0f;
                    enemy->ActionNow->m_Transform.translation.x -= pushSpeed;
                }
            }
        }
    }

    int Fighter::GetNewDirection() {
        float myPushboxPos=GetCurrentPosition().x+GetCurrentPushbox().x/2+GetCurrentPushboxOffset().x;
        float enemyPos=enemy->GetCurrentPosition().x+enemy->GetCurrentPushboxOffset().x;
        float myPos=GetCurrentPosition().x+GetCurrentPushboxOffset().x;
        float enemyPushboxPos=enemy->GetCurrentPosition().x+enemy->GetCurrentPushbox().x/2+enemy->GetCurrentPushboxOffset().x;
        if(myPushboxPos<=enemyPos) {
            return static_cast<int>(FighterDirection::Left);
        }
        else if(myPos>=enemyPushboxPos) {
            return static_cast<int>(FighterDirection::Right);
        }
        return direction;
    }

    void Fighter::SkillDetection() {
        for(auto skill:SpecificStates.SpecialStates) {
            if(SpecialMoveData.SkillCommand.count(skill)) {
                if (controller->IsSpecialMove(SpecialMoveData.SkillCommand[skill])&&SpecificStates.IdleStates.count(currentState)) {ChangeState(skill);}
            }
        }
    }

    void Fighter::SkillErrorPrevent(Keys key, const std::vector<Keys>& reqType) {
        if (!controller->IsInDomainKey(key,reqType)) {
            ClearButtonType();
            ChangeState(FighterState::Idle);
        }
    }

    void Fighter::UpdateStateAndNewXY() {
        auto currentEnter = StateUpdate.find(currentState);
        currentEnter->second();

        glm::vec2 position={ActionNow->GetTransform().translation.x+direction*velocity.x,
            ActionNow->GetTransform().translation.y+velocity.y};
        ActionNow->SetTransform({position,0,{direction,1}});
    }

    void Fighter::HitboxIsCollidedEnemy() {
        if(currentAnimationIndex!=ActionNow->GetCurrentFrameIndex()){AttackStruck=false;}
        if(AttackStruck==true||GetCurrentHitboxOffset()==glm::vec2{-1,-1}){ return;}

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
                glm::vec2 EffectPos=enemyPos+BodyOffset-glm::vec2{12,12}+glm::vec2{GetRandomNum(0,24),GetRandomNum(0,24)};
                if(!SpecificStates.Invincible.count(enemy->currentState)) {
                    if(enemy->IsBlocking()) {
                        if(SpecificStates.SpecialStates.count(currentState)) {enemy->GetAttack(GetAttackNum()/5);}
                        enemy->AddEffect(GetHitStrength(),BeHitType::Block,EffectPos);
                        enemy->AttackBlock();
                        HitEnemy=true;
                    }
                    else {
                        AttackHit(GetHitStrength(),static_cast<HitLocation>(i),GetAttackNum());
                        enemy->AddEffect(GetHitStrength(),BeHitType::Hit,EffectPos);
                        enemy->GetSFX()[enemy->GetCurrentState()]->Play();
                        HitEnemy=true;
                    }
                    currentAnimationIndex=ActionNow->GetCurrentFrameIndex();
                    AttackStruck=true;
                    return;
                }
            }
        }
    }

    void Fighter::AttackBlock() {
        FighterState newState=GetBlockState();
        ChangeState(newState);
    }

    void Fighter::AttackHit(HitStrength Strength,HitLocation Location,float dmg) {
        enemy->GetAttack(dmg);
        FighterState newState=GetBeHitState(Strength,Location);
        enemy->ChangeState(newState);
    }

    bool Fighter::IsBlocking() {
        if(!SpecificStates.HurtStates.count(currentState)) {
            if(SpecificStates.CanBlockStates.count(currentState)) {
                switch(enemy->GetAttackType()){
                    case AttackType::Upper:
                        if(SpecificStates.StandStates.count(currentState)) {
                            return controller->IsBackward(direction);
                        }
                        break;
                    case AttackType::Lower:
                        if(SpecificStates.CrouchStates.count(currentState)) {
                            return controller->IsBackward(direction);
                        }
                        break;
                    case AttackType::Null:
                        return controller->IsBackward(direction);
                    default:
                        return false;
                }
            }
        }
        return false;
    }

    FighterState Fighter::GetBeHitState(HitStrength Strength,HitLocation Location) {
        if(!enemy->GetCharacterIsOnFloor()) {
            switch (Strength) {
                case HitStrength::L:
                    return FighterState::KnockDownL;
                break;
                case HitStrength::M:
                    return FighterState::KnockDownM;
                break;
                case HitStrength::H:
                    return FighterState::KnockDownH;
                break;
                default:
                    return FighterState::Idle;
            }
        }
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
        if(SpecificStates.StandStates.count(currentState)) {
            return FighterState::BackwardBlock;
        }
        if(SpecificStates.CrouchStates.count(currentState)) {
            return FighterState::CrouchBlock;
        }
        return FighterState::Idle;
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
            ChangeState(FighterState::CrouchUp);
        }
        if (Input::IsKeyDown(Keycode::NUM_2)) {
            ChangeState(FighterState::KnockDownL);
        }
        if (Input::IsKeyDown(Keycode::NUM_3)) {
            ChangeState(FighterState::KnockDownM);
        }
        if (Input::IsKeyDown(Keycode::NUM_4)) {
            ChangeState(FighterState::KnockDownH);
        }
        if (Input::IsKeyDown(Keycode::NUM_5)) {
            ChangeState(FighterState::GetUp);
        }
        if (Input::IsKeyDown(Keycode::NUM_6)) {
            ChangeState(FighterState::JumpAttackEnd);
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

    void Fighter::Update(std::shared_ptr<Core::Context> context,std::shared_ptr<Controller> controller,glm::vec2 cameraOffset) {
        PostionTester();
        PushBoxTester();
        PrintPostion();

        this->controller=controller;
        SkillDetection();
        UpdateStateAndNewXY();
        ReSize();
        BorderDetection(context->GetWindowWidth()/2,cameraOffset);
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

    void Fighter::DrawCharacter(glm::vec2 cameraOffset) {
        ActionNow->custom_Draw(cameraOffset);
        pushboxPicture->custom_Draw(cameraOffset);
        headPicture->custom_Draw(cameraOffset);
        bodyPicture->custom_Draw(cameraOffset);
        legPicture->custom_Draw(cameraOffset);
        if(GetCurrentHitboxOffset()!=glm::vec2{-1,-1}) {
            hitPicture->custom_Draw(cameraOffset);
        }
    }
    //Actions
    void Fighter::IdleStateEnter(){
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::IdleStateUpdate() {
        if (GetAnimationIsEnd()) {ActionNow->AnimationPlay();}
        else if (controller->IsForward(direction)) {ChangeState(FighterState::Forward);}
        else if (controller->IsBackward(direction)) {ChangeState(FighterState::Backward);}
        else if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::CrouchDown);}
        else if (controller->IsKeyDown(Keys::UP)) {ChangeState(FighterState::JumpUP);}
        else if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::LP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::MP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::HP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::LK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::MK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::HK);}
        direction=GetNewDirection();
    }

    void Fighter::WalkStateEnter(){
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::ForwardStateUpdate() {
        if (GetAnimationIsEnd()) {ActionNow->AnimationPlay();}
        if (!controller->IsForward(direction)) {ChangeState(FighterState::Idle);}
        if (controller->IsKeyDown(Keys::UP)) {ChangeState(FighterState::JumpForward);}
        if (controller->IsKeyPressed(Keys::DOWN)) {ChangeState(FighterState::CrouchDown);}
        if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::LP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::MP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::HP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::LK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::MK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::HK);}
        direction=GetNewDirection();
    }
    void Fighter::BackwardStateUpdate() {
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
        direction=GetNewDirection();
    }

    void Fighter::JumpStateEnter(){
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::JumpStateUpdate(){
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::JumpLP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::JumpMP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::JumpHP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::JumpLK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::JumpMK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::JumpHK);}
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::CrouchEnter(){
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::CrouchUpdate() {
        if (!controller->IsKeyPressed(Keys::DOWN)){ChangeState(FighterState::CrouchUp);}
        else if (controller->IsKeyDown(Keys::LP)) {ChangeState(FighterState::CrouchLP);}
        else if (controller->IsKeyDown(Keys::MP)) {ChangeState(FighterState::CrouchMP);}
        else if (controller->IsKeyDown(Keys::HP)) {ChangeState(FighterState::CrouchHP);}
        else if (controller->IsKeyDown(Keys::LK)) {ChangeState(FighterState::CrouchLK);}
        else if (controller->IsKeyDown(Keys::MK)) {ChangeState(FighterState::CrouchMK);}
        else if (controller->IsKeyDown(Keys::HK)) {ChangeState(FighterState::CrouchHK);}
        direction=GetNewDirection();
    }
    void Fighter::CrouchDownUpdate() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Crouch);}
    }
    void Fighter::CrouchUpUpdate() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::AttackStateEnter() {
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        PlayCurrentSound();
    }
    void Fighter::AttackStateUpdate() {
        if(enemy->GetCharacterIsInBorder()&&HitEnemy
            &&(enemy->SpecificStates.HurtStates.count(enemy->currentState)||
                enemy->SpecificStates.BlockStates.count(enemy->currentState)))
            {velocity.x=enemy->GetVelocity().x;}
        if (GetAnimationIsEnd()&&SpecificStates.CrouchAttackStates.count(currentState)) {ChangeState(FighterState::Crouch);}
        else if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Fighter::JumpAttackStateEnter() {
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::JumpAttackStateUpdate() {
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if(GetAnimationIsEnd()){ChangeState(FighterState::JumpAttackEnd);}
        if(GetCharacterIsOnFloor()){ChangeState(FighterState::Idle);}
        //here
    }
    void Fighter::JumpAttackEndStateEnter() {
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::JumpAttackEndStateUpdate() {
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if(GetCharacterIsOnFloor()){ChangeState(FighterState::Idle);}
        //here
    }
    void Fighter::HurtStateEnter() {
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::HurtStateUpdate() {
        velocity.x+=Friction*Time::GetDeltaTimeMs()/1000;
        velocity.y+=Gravity*Time::GetDeltaTimeMs()/1000;
        direction=GetNewDirection();
        if (GetAnimationIsEnd()&&velocity.x>=0&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::KnockDownStateEnter() {
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::KnockDownStateUpdate() {
        velocity.x+=Friction*Time::GetDeltaTimeMs()/1000;
        velocity.y+=Gravity*Time::GetDeltaTimeMs()/1000;
        if(velocity.x>0){velocity.x=0;}
        if (GetAnimationIsEnd()&&velocity.x<=0&&GetCharacterIsOnFloor()) {ChangeState(FighterState::GetUp);}
    }

    void Fighter::GetUpStateEnter() {
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::GetUpStateUpdate() {
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }

    void Fighter::BlockStateEnter() {
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        PlayCurrentSound();
    }
    void Fighter::BlockStateUpdate() {
        velocity.x+=Friction/2*Time::GetDeltaTimeMs()/1000;
        direction=GetNewDirection();
        if (GetAnimationIsEnd()&&velocity.x>=0&&currentState==FighterState::CrouchBlock) {ChangeState(FighterState::Crouch);}
        else if (GetAnimationIsEnd()&&velocity.x>=0&&currentState==FighterState::BackwardBlock) {ChangeState(FighterState::Idle);}
    }
    void Fighter::WinStateEnter() {
        PlayCurrentSound();
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::WinStartStateUpdate() {
        if (GetAnimationIsEnd()){ChangeState(FighterState::Win);}
    }
    void Fighter::WinStateUpdate() {
        if (GetAnimationIsEnd()){ActionNow->AnimationPlay();}
    }
    void Fighter::LossStateEnter() {
        PlayCurrentSound();
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Fighter::LossStateUpdate() {
        if(velocity.x<0){velocity.x+=Friction*Time::GetDeltaTimeMs()/1000;}
        else{velocity.x=0;}
        if(GetCharacterIsOnFloor()&&velocity.y<0){velocity.y=0;}
        else{velocity.y+=Gravity*Time::GetDeltaTimeMs()/1000;}
    }
}