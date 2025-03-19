//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ken.hpp"
namespace Util {
    Ken::Ken(): Fighter("Ken",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ken/Ken_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ken/Ken_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/KenTheme.mp3");
        country_position={{338, 245},0,{1,1}};
        BackgroundInit(14);
        Ken::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Ken::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(6,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(4, "MP");
        animations[FighterState::JumpUP] = ActionInit(8, "JumpUP");
        animations[FighterState::LK] = ActionInit(5, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");


        frames[FighterState::Idle]={100, 150, 200, 150, 100,120};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::LP]={180,240,180};
        frames[FighterState::MP]={120,120,300};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120,120};
        frames[FighterState::LK]={100,100,100,100,100};
        frames[FighterState::MK]={100,100,120,100,100};
        frames[FighterState::HK]={120,120,120,120,120};
    }

    void Ken::IdleStateEnter(){
        velocity={0,0};
        SetAnimation(FighterState::Idle,frames[FighterState::Idle]);
    }
    void Ken::IdleStateUpload() {
        if (Input::IsKeyPressed(Keycode::D)) {
            if (direction > 0) {ChangeState(FighterState::Forward);}
            else {ChangeState(FighterState::Backward);}
        }
        else if (Input::IsKeyPressed(Keycode::A)) {
            if (direction < 0) {ChangeState(FighterState::Forward);}
            else {ChangeState(FighterState::Backward);}
        }
        else if (Input::IsKeyDown(Keycode::T)) {
            ChangeState(FighterState::LP);
        }
        else if (Input::IsKeyDown(Keycode::Y)) {
            ChangeState(FighterState::MP);
        }
        else if (Input::IsKeyDown(Keycode::W)) {
            ChangeState(FighterState::JumpUP);
        }
        else if (Input::IsKeyDown(Keycode::G)) {
            ChangeState(FighterState::LK);
        }
        else if (Input::IsKeyDown(Keycode::H)) {
            ChangeState(FighterState::MK);
        }
        else if (Input::IsKeyDown(Keycode::J)) {
            ChangeState(FighterState::HK);
        }
    }
    void Ken::ForwardStateEnter() {
        velocity.x=direction*150;
        SetAnimation(FighterState::Forward,frames[FighterState::Forward]);
    }
    void Ken::ForwardStateUpload() {
        if ((Input::IsKeyUp(Keycode::D)&&direction>0)||(Input::IsKeyUp(Keycode::A)&&direction<0)) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::BackwardStateEnter() {
        velocity.x=direction*-150;
        SetAnimation(FighterState::Backward,frames[FighterState::Backward]);
    }
    void Ken::BackwardStateUpload() {
        if ((Input::IsKeyUp(Keycode::A)&&direction>0)||(Input::IsKeyUp(Keycode::D)&&direction<0)) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::LPStateEnter() {
        SetAnimation(FighterState::LP,frames[FighterState::LP]);
    }
    void Ken::LPStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::MPStateEnter(){
        SetAnimation(FighterState::MP,frames[FighterState::MP]);
    }
    void Ken::MPStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::JumpUPStateEnter(){
        velocity.y=Initialvelocity.Jump;
        SetAnimation(FighterState::JumpUP,frames[FighterState::JumpUP]);
    }
    void Ken::JumpUPStateUpload() {
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::LKStateEnter() {
        SetAnimation(FighterState::LK,frames[FighterState::LK]);
    }
    void Ken::LKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::MKStateEnter() {
        SetAnimation(FighterState::MK,frames[FighterState::MK]);
    }
    void Ken::MKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ken::HKStateEnter() {
        SetAnimation(FighterState::HK,frames[FighterState::HK]);
    }
    void Ken::HKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }

}