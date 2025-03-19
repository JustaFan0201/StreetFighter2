//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ryu.hpp"
namespace Util {
    Ryu::Ryu(): Fighter("Ryu",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ryu/Ryu_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ryu/Ryu_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/RyuTheme.mp3");
        country_position={{14,90},0,{1,1}};
        BackgroundInit(15);
        Ryu::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Ryu::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(5,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::JumpUP] = ActionInit(7, "JumpUP");
        animations[FighterState::LK] = ActionInit(4, "LK");
        animations[FighterState::MK] = ActionInit(4, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");


        frames[FighterState::Idle]={100, 150, 200, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::LP]={180,240,180};
        frames[FighterState::MP]={120,120,300,120,120};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120};
        frames[FighterState::LK]={120,120,120};
        frames[FighterState::MK]={120,120,120};
        frames[FighterState::HK]={120,120,120,120,120};
    }
    void Ryu::IdleStateEnter(){
        velocity={0,0};
        SetAnimation(FighterState::Idle,frames[FighterState::Idle]);
    }
    void Ryu::IdleStateUpload() {
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
    void Ryu::ForwardStateEnter() {
        velocity.x=direction*150;
        SetAnimation(FighterState::Forward,frames[FighterState::Forward]);
    }
    void Ryu::ForwardStateUpload() {
        if ((Input::IsKeyUp(Keycode::D)&&direction>0)||(Input::IsKeyUp(Keycode::A)&&direction<0)) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::BackwardStateEnter() {
        velocity.x=direction*-150;
        SetAnimation(FighterState::Backward,frames[FighterState::Backward]);
    }
    void Ryu::BackwardStateUpload() {
        if ((Input::IsKeyUp(Keycode::A)&&direction>0)||(Input::IsKeyUp(Keycode::D)&&direction<0)) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::LPStateEnter() {
        SetAnimation(FighterState::LP,frames[FighterState::LP]);
    }
    void Ryu::LPStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::MPStateEnter(){
        SetAnimation(FighterState::MP,frames[FighterState::MP]);
    }
    void Ryu::MPStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::JumpUPStateEnter(){
        velocity.y=Initialvelocity.Jump;
        SetAnimation(FighterState::JumpUP,frames[FighterState::JumpUP]);
    }
    void Ryu::JumpUPStateUpload() {
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::LKStateEnter() {
        SetAnimation(FighterState::LK,frames[FighterState::LK]);
    }
    void Ryu::LKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::MKStateEnter() {
        SetAnimation(FighterState::MK,frames[FighterState::MK]);
    }
    void Ryu::MKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::HKStateEnter() {
        SetAnimation(FighterState::HK,frames[FighterState::HK]);
    }
    void Ryu::HKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }

}