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
        Ryu::LoadOffsetVelocity();
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
        animations[FighterState::JumpUP] = ActionInit(7, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(6, "JumpForward");
        animations[FighterState::JumpBackward] = ActionInit(6, "JumpBackward");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::LK] = ActionInit(4, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");

        frames[FighterState::Idle]={100, 150, 200, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120};
        frames[FighterState::JumpForward]={120,120,120,120,120,120};
        frames[FighterState::JumpBackward]={120,120,120,120,120,120};
        frames[FighterState::LP]={180,240,180};
        frames[FighterState::MP]={120,120,300,120,120};
        frames[FighterState::LK]={120,120,120,120};
        frames[FighterState::MK]={120,120,120,120,120};
        frames[FighterState::HK]={120,120,120,120,120};
    }
    void Ryu::LoadOffsetVelocity() {
        Initialvelocity.x[FighterState::Forward]=400;
        Initialvelocity.x[FighterState::Backward]=-400;
        Initialvelocity.x[FighterState::JumpForward]=500;
        Initialvelocity.x[FighterState::JumpBackward]=-500;
        Initialvelocity.y[FighterState::JumpForward]=1700;
        Initialvelocity.y[FighterState::JumpBackward]=1700;
        Initialvelocity.y[FighterState::JumpUP]=1600;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Forward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Backward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::JumpUP]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::JumpForward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::JumpBackward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::LP]={{0,0},{0,0},{0,0}};
        offset[FighterState::MP]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::LK]={{0,0},{0,0},{0,0},{0,0},};
        offset[FighterState::MK]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::HK]={{-90,9},{-72,9},{-46,9},{-72,0},{-99,0}};
    }
    void Ryu::IdleStateEnter(){
        velocity={0,0};
        SetAnimation(currentState,frames[currentState],offset[currentState]);
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

        else if (Input::IsKeyDown(Keycode::W)) {
            ChangeState(FighterState::JumpUP);
        }
        else if (Input::IsKeyDown(Keycode::T)) {
            ChangeState(FighterState::LP);
        }
        else if (Input::IsKeyDown(Keycode::Y)) {
            ChangeState(FighterState::MP);
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

    void Ryu::WalkStateEnter() {
        velocity.x=direction*Initialvelocity.x[currentState];
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::WalkStateUpload() {
        switch (currentState) {
            case FighterState::Forward:
                if (Input::IsKeyDown(Keycode::W)) {
                    if (direction > 0) {ChangeState(FighterState::JumpForward);}
                    else {ChangeState(FighterState::JumpBackward);}
                }
                if ((Input::IsKeyUp(Keycode::D)&&direction>0)||(Input::IsKeyUp(Keycode::A)&&direction<0)) {
                    ChangeState(FighterState::Idle);
                }
            break;
            case FighterState::Backward:
                if (Input::IsKeyDown(Keycode::W)) {
                    if (direction < 0) {ChangeState(FighterState::JumpForward);}
                    else {ChangeState(FighterState::JumpBackward);}
                }
                if ((Input::IsKeyUp(Keycode::A)&&direction>0)||(Input::IsKeyUp(Keycode::D)&&direction<0)) {
                    ChangeState(FighterState::Idle);
                }
            break;
            default:
                break;
        }
    }

    void Ryu::JumpStateEnter(){
        velocity.x=direction*Initialvelocity.x[currentState];
        velocity.y=Initialvelocity.y[currentState];
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::JumpStateUpload(){
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {
            ChangeState(FighterState::Idle);
        }
    }


    void Ryu::LPStateEnter() {
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::LPStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::MPStateEnter(){
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::MPStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::LKStateEnter() {
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::LKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::MKStateEnter() {
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::MKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }
    void Ryu::HKStateEnter() {
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::HKStateUpload() {
        if (GetAnimationIsEnd()) {
            ChangeState(FighterState::Idle);
        }
    }

}