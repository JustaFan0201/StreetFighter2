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
        StateInit();
        Ken::LoadAnimations();
        Ken::LoadOffsetVelocity();
        Ken::LoadAllBox();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Ken::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(6,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::JumpUP] = ActionInit(7, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(7, "JumpForward");
        animations[FighterState::JumpBackward] = ActionInit(7, "JumpBackward");
        animations[FighterState::Crouchdown] = ActionInit(3, "Crouchdown");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::HP] = ActionInit(6, "HP");
        animations[FighterState::LK] = ActionInit(4, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");

        frames[FighterState::Idle]={100, 150, 200, 150, 100, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120};
        frames[FighterState::JumpForward]={60,90,90,120,90,90,60};
        frames[FighterState::JumpBackward]={60,90,90,120,90,90,60};
        frames[FighterState::Crouchdown]={60,60,60};
        frames[FighterState::LP]={30,60,90};
        frames[FighterState::MP]={30,60,120,60,30};
        frames[FighterState::HP]={60,90,180,90,60,60};
        frames[FighterState::LK]={30,60,90,60};
        frames[FighterState::MK]={30,60,120,60,30};
        frames[FighterState::HK]={60,90,180,90,90};
    }
    void Ken::LoadOffsetVelocity() {
        Gravity=-4800;
        Initialvelocity.x[FighterState::Forward]=400;
        Initialvelocity.x[FighterState::Backward]=-400;
        Initialvelocity.x[FighterState::JumpForward]=500;
        Initialvelocity.x[FighterState::JumpBackward]=-500;
        Initialvelocity.y[FighterState::JumpForward]=2100;
        Initialvelocity.y[FighterState::JumpBackward]=2100;
        Initialvelocity.y[FighterState::JumpUP]=2000;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Crouchdown]={{10,-9},{31,-30},{35,-43}};
        offset[FighterState::LP]={{5,3},{44,2},{3,3}};
        offset[FighterState::MP]={{14,5},{-9,5},{56,5},{-10,6},{15,6}};
        offset[FighterState::HP]={{15,5},{23,5},{67,5},{40,34},{23,6},{15,5}};
        offset[FighterState::LK]={{15,6},{64,4},{140,4},{64,5}};
        offset[FighterState::MK]={{20,12},{-25,10},{-25,10},{-27,9},{23,11}};
        offset[FighterState::HK]={{32,5},{45,12},{68,11},{44,-11},{3,-9}};
        offset[FighterState::HK]={{32,5},{45,12},{68,11},{44,-11},{3,-9}};
    }
    void Ken::LoadAllBox() {
        boxes.pushbox.size[FighterState::Idle]={100,200};
        boxes.pushbox.size[FighterState::Crouchdown]={100,120};
        boxes.pushbox.offset[FighterState::Idle]={15,0};
        boxes.pushbox.offset[FighterState::Crouchdown]={15,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={25,25};
        boxes.hurtbox.body.size[FighterState::Idle]={50,50};
        boxes.hurtbox.leg.size[FighterState::Idle]={25,25};

        boxes.hurtbox.head.offset[FighterState::Idle]={0,50};
        boxes.hurtbox.body.offset[FighterState::Idle]={0,0};
        boxes.hurtbox.leg.offset[FighterState::Idle]={0,-50};
    }
}