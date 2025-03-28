//
// Created by asus on 2025/2/27.
//

#include "Fighters/Blanka.hpp"
namespace Util {
    Blanka::Blanka(): Fighter("Blanka",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Blanka/Blanka_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Blanka/Blanka_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/brazil.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/BlankaTheme.mp3");
        country_position={{323, 23},0,{1,1}};
        BackgroundInit(4);
        StateInit();
        Blanka::LoadAnimations();
        Blanka::LoadOffsetVelocity();
        Blanka::LoadAllBox();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Blanka::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(3,"Idle");
        animations[FighterState::Backward] = ActionInit(8,"Backward");
        animations[FighterState::Forward] = ActionInit(8,"Forward");
        animations[FighterState::JumpUP] = ActionInit(8, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(6, "JumpForward");
        animations[FighterState::JumpBackward] = ActionInit(6, "JumpForward");
        animations[FighterState::Crouchdown] = ActionInit(3, "Crouchdown");
        animations[FighterState::LP] = ActionInit(6, "LP");
        animations[FighterState::MP] = ActionInit(4, "MP");
        animations[FighterState::HP] = ActionInit(6, "HP");
        animations[FighterState::LK] = ActionInit(6, "LK");
        animations[FighterState::MK] = ActionInit(6, "MK");
        animations[FighterState::HK] = ActionInit(7, "HK");

        frames[FighterState::Idle]={100, 150, 150};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpForward]={60,90,120,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,120,90,60};
        frames[FighterState::Crouchdown]={60,60,60};
        frames[FighterState::LP]={60,60,60,60,60,60};
        frames[FighterState::MP]={30,60,60,30};
        frames[FighterState::HP]={60,60,60,60,60,60};
        frames[FighterState::LK]={60,60,60,60,60,60};
        frames[FighterState::MK]={60,60,60,60,60,60};
        frames[FighterState::HK]={60,60,60,60,60,60,60};
    }
    void Blanka::LoadOffsetVelocity() {
        Gravity=-4800;
        Initialvelocity.x[FighterState::Forward]=400;
        Initialvelocity.x[FighterState::Backward]=-400;
        Initialvelocity.x[FighterState::JumpForward]=500;
        Initialvelocity.x[FighterState::JumpBackward]=-500;
        Initialvelocity.y[FighterState::JumpForward]=2100;
        Initialvelocity.y[FighterState::JumpBackward]=2100;
        Initialvelocity.y[FighterState::JumpUP]=2000;

        offset[FighterState::Idle]={{0,0},{0,6},{-5,8}};
        offset[FighterState::Crouchdown]={{-21,0},{-48,-5},{-62,-6}};
        offset[FighterState::LP]={{-82,-2},{-61,3},{-53,-3},{-56,1},{-13,-1},{-77,0}};
        offset[FighterState::MP]={{-42,51},{-34,19},{-15,2},{-55,-3}};
        offset[FighterState::HP]={{-83,-6},{-58,-1},{-141,31},{-114,1},{-54,-12},{-77,-6}};
        offset[FighterState::LK]={{4,1},{59,2},{142,4},{72,7},{-1,3},{-12,-1}};
        offset[FighterState::MK]={{17,8},{-106,32},{-100,35},{-108,37},{-55,36},{1,-6}};
        offset[FighterState::HK]={{-63,-11},{-61,-16},{-74,9},{-155,56},{-176,28},{-38,-11}};

    }
    void Blanka::LoadAllBox() {
            boxes.pushbox.size[FighterState::Idle]={100,200};
            boxes.pushbox.size[FighterState::Crouchdown]={100,120};
            boxes.pushbox.offset[FighterState::Idle]={15,0};
            boxes.pushbox.offset[FighterState::Crouchdown]={15,-43};

            boxes.hurtbox.head.size[FighterState::Idle]={50,50};
            boxes.hurtbox.body.size[FighterState::Idle]={100,100};
            boxes.hurtbox.leg.size[FighterState::Idle]={100,125};

            boxes.hurtbox.head.offset[FighterState::Idle]={{23,113},{28,110},{27,109},{26,117},{25,116}};
            boxes.hurtbox.body.offset[FighterState::Idle]={{-15,57},{-15,57},{-10,55},{-10,54},{-12,53}};
            boxes.hurtbox.leg.offset[FighterState::Idle]={{-12,-53},{-12,-52},{-12,-52},{-12,-52},{-11,-48}};
        }
}
