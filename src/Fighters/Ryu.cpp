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
        StateInit();
        Ryu::LoadAnimations();
        Ryu::LoadOffsetVelocity();
        Ryu::LoadAllBox();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            120,
            true,
            4
        );

        BlackPicture=std::make_shared<AnimationSpace>(
                std::vector<std::string> {RESOURCE_DIR"/EditMaterial/black.png"},
                true,
                120,
                true,
                6
                );
    }
    void Ryu::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(5,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::JumpUP] = ActionInit(7, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(6, "JumpForward");
        animations[FighterState::JumpBackward] = ActionInit(6, "JumpBackward");
        animations[FighterState::Crouchdown] = ActionInit(3, "Crouchdown");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::HP] = ActionInit(6, "HP");
        animations[FighterState::LK] = ActionInit(4, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");

        frames[FighterState::Idle]={100, 150, 200, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120};
        frames[FighterState::JumpForward]={60,90,120,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,120,90,60};
        frames[FighterState::Crouchdown]={60,60,60};
        frames[FighterState::LP]={30,60,90};
        frames[FighterState::MP]={30,60,120,60,30};
        frames[FighterState::HP]={60,90,180,90,60,60};
        frames[FighterState::LK]={30,60,90,60};
        frames[FighterState::MK]={30,60,120,60,30};
        frames[FighterState::HK]={60,90,180,90,90};
    }
    void Ryu::LoadOffsetVelocity() {
        Initialvelocity.x[FighterState::Forward]=400;
        Initialvelocity.x[FighterState::Backward]=-400;
        Initialvelocity.x[FighterState::JumpForward]=500;
        Initialvelocity.x[FighterState::JumpBackward]=-500;
        Initialvelocity.y[FighterState::JumpForward]=2100;
        Initialvelocity.y[FighterState::JumpBackward]=2100;
        Initialvelocity.y[FighterState::JumpUP]=2000;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Forward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Backward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::JumpUP]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::JumpForward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::JumpBackward]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Crouchdown]={{10,-9},{31,-30},{35,-43}};
        offset[FighterState::LP]={{5,3},{44,2},{3,3}};
        offset[FighterState::MP]={{14,5},{-9,5},{56,5},{-10,6},{15,6}};
        offset[FighterState::HP]={{15,5},{23,5},{67,5},{40,34},{23,6},{15,5}};
        offset[FighterState::LK]={{15,6},{64,4},{140,4},{64,5}};
        offset[FighterState::MK]={{20,12},{-25,10},{-25,10},{-27,9},{23,11}};
        offset[FighterState::HK]={{32,5},{45,12},{68,11},{44,-11},{3,-9}};
        offset[FighterState::HK]={{32,5},{45,12},{68,11},{44,-11},{3,-9}};
    }
    void Ryu::LoadAllBox() {
        pushbox.size[FighterState::Idle]={100,200};
        pushbox.size[FighterState::Forward]={100,200};
        pushbox.size[FighterState::Backward]={100,200};
        pushbox.size[FighterState::JumpUP]={100,200};
        pushbox.size[FighterState::JumpForward]={100,200};
        pushbox.size[FighterState::JumpBackward]={100,200};
        pushbox.size[FighterState::Crouchdown]={100,120};
        pushbox.size[FighterState::LP]={100,200};
        pushbox.size[FighterState::MP]={100,200};
        pushbox.size[FighterState::HP]={100,200};
        pushbox.size[FighterState::LK]={100,200};
        pushbox.size[FighterState::MK]={100,200};
        pushbox.size[FighterState::HK]={100,200};
        pushbox.size[FighterState::HK]={100,200};
    }
    void Ryu::IdleStateEnter(){
        velocity={0,0};
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::IdleStateUpload() {
        if (GetAnimationIsEnd()) {
            ActionNow->AnimationPlay();
        }
        if (Input::IsKeyPressed(Keycode::D)) {
            if (direction > 0) {ChangeState(FighterState::Forward);}
            else {ChangeState(FighterState::Backward);}
        }
        else if (Input::IsKeyPressed(Keycode::A)) {
            if (direction < 0) {ChangeState(FighterState::Forward);}
            else {ChangeState(FighterState::Backward);}
        }
        else if (Input::IsKeyPressed(Keycode::S)) {
            ChangeState(FighterState::Crouchdown);
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
        else if (Input::IsKeyDown(Keycode::U)) {
            ChangeState(FighterState::HP);
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
        if (GetAnimationIsEnd()) {
            ActionNow->AnimationPlay();
        }
        switch (currentState) {
            case FighterState::Forward:
                if (Input::IsKeyDown(Keycode::W)) {
                    ChangeState(FighterState::JumpForward);
                }
                if ((Input::IsKeyUp(Keycode::D) && direction > 0) ||
                    (Input::IsKeyUp(Keycode::A) && direction < 0)) {
                    ChangeState(FighterState::Idle);
                    }
            break;
            case FighterState::Backward:
                if (Input::IsKeyDown(Keycode::W)) {
                    ChangeState(FighterState::JumpBackward);
                }
                if ((Input::IsKeyUp(Keycode::A) && direction > 0) ||
                    (Input::IsKeyUp(Keycode::D) && direction < 0)) {
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

    void Ryu::CrouchdownEnter(){
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::CrouchdownUpload() {
        if (Input::IsKeyUp(Keycode::S)){
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

    void Ryu::HPStateEnter(){
        SetAnimation(currentState,frames[currentState],offset[currentState]);
    }
    void Ryu::HPStateUpload() {
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