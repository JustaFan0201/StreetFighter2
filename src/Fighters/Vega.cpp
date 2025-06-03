//
// Created by asus on 2025/5/29.
//

#include "Fighters/Vega.hpp"
namespace Util {
    Vega::Vega(): Fighter("Vega") {
        LoadFighterData();
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/thailand.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/thailand_dark.png");
        country_position={{14,-20},0,{1,1}};
        face_postion={{265, -201},0,{1,1}};
        BackgroundInit(4);
        StateInit();
        LoadCommonVelocities();
        Vega::LoadAnimations();
        Vega::LoadOffsetVelocity();
        Vega::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Vega::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Vega::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(4,"Idle");
        animations[FighterState::Forward] = animations[FighterState::Backward] = ActionInit(4,"Forward");
        animations[FighterState::JumpUP] = animations[FighterState::JumpForward] = ActionInit(5, "JumpUP");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(2, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;

        animations[FighterState::LP] = ActionInit(7, "LP");
        animations[FighterState::HP] =animations[FighterState::MP] = ActionInit(9, "MP");
        animations[FighterState::LK] = ActionInit(5, "LK");
        animations[FighterState::HK] =animations[FighterState::MK] = ActionInit(6, "MK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(4, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(3, "GetUp");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(1, "CrouchBlock");

        animations[FighterState::CrouchHP] = animations[FighterState::CrouchMP] =animations[FighterState::CrouchLP] = ActionInit(7, "CrouchLP");
        animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");
        animations[FighterState::CrouchHK] = ActionInit(3, "CrouchHK");

        animations[FighterState::JumpHP] =animations[FighterState::JumpMP] =animations[FighterState::JumpLP] = ActionInit(3, "JumpLP");
        animations[FighterState::JumpLK] = ActionInit(2, "JumpLK");
        animations[FighterState::JumpMK] = ActionInit(3, "JumpMK");
        animations[FighterState::JumpHK] = ActionInit(3, "JumpHK");
        animations[FighterState::JumpAttackEnd] = ActionInit(1, "JumpAttackEnd");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(4, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(2, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(5, "DefeatedLoss");

        frames[FighterState::Idle]={120, 150, 150, 120};
        frames[FighterState::Forward]=frames[FighterState::Backward]={120, 150, 150, 120};
        frames[FighterState::JumpUP]=frames[FighterState::JumpForward]={90,120,150,120,90};
        std::vector<int> reversedframe = frames[FighterState::JumpForward];
        std::reverse(reversedframe.begin(), reversedframe.end());
        frames[FighterState::JumpBackward] = reversedframe;
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60};
        frames[FighterState::CrouchUp]={60,60};
        frames[FighterState::LP]={60,80,80,80,80,60,60};
        frames[FighterState::MP]={70,95,95,95,95,70,70};
        frames[FighterState::HP]={80,110,110,110,110,110,80};
        frames[FighterState::LK]={50,60,90,60,50};
        frames[FighterState::MK]={60,90,100,110,90,60};
        frames[FighterState::HK]={70,100,110,130,100,70};

        frames[FighterState::CrouchLP]={60,70,70,90,90,50,50};
        frames[FighterState::CrouchMP]={70,80,80,110,110,60,60};
        frames[FighterState::CrouchHP]={80,90,90,120,120,70,70};
        frames[FighterState::CrouchLK]={60,90,60};
        frames[FighterState::CrouchMK]={80,120,80};
        frames[FighterState::CrouchHK]={110,170,80};

        frames[FighterState::JumpLP]={80,120,80};
        frames[FighterState::JumpMP]={90,140,90};
        frames[FighterState::JumpHP]={100,170,100};
        frames[FighterState::JumpLK]={80,110};
        frames[FighterState::JumpMK]={80,80,110};
        frames[FighterState::JumpHK]={90,140,90};
        frames[FighterState::JumpAttackEnd]={100};

        frames[FighterState::HurtHeadL] = {90,90};
        frames[FighterState::HurtHeadM] = {160,160};
        frames[FighterState::HurtHeadH] = {210,210};
        frames[FighterState::HurtBodyL] = {90,90};
        frames[FighterState::HurtBodyM] = {160,160};
        frames[FighterState::HurtBodyH] = {210,210};

        frames[FighterState::KnockDownL] = {80,85,140,85};
        frames[FighterState::KnockDownM] = {105,110,140,95};
        frames[FighterState::KnockDownH] = {110,140,210,140,90};
        frames[FighterState::GetUp] = {140,150,130};

        frames[FighterState::BackwardBlock] = {60,60};
        frames[FighterState::CrouchBlock] = {100};

        frames[FighterState::WinStart]={200};
        frames[FighterState::Win]={200, 200, 200, 200};

        frames[FighterState::TimeOverLoss]={180, 180};
        frames[FighterState::DefeatedLoss]={180,180,180,180,180};
    }
    void Vega::LoadOffsetVelocity() {
        offset[FighterState::Idle]={{0,0},{0,-2},{-3,-7},{-1,-4}};
        offset[FighterState::Crouch]={{-1,-52}};
        offset[FighterState::CrouchDown]={{-1,-10},{1,-38}};
        offset[FighterState::CrouchUp]={{1,-38},{-1,-10}};
        //Stand attack offset
        offset[FighterState::LP]={{125,142},{123,133},{151,140},{152,139},{153,140},{152,139},{120,132}};
        offset[FighterState::HP]=offset[FighterState::MP]={{-32,-11},{-49,-20},{-50,-17},{-9,-25},{-8,-26},{-8,-23},{-8,-26},{-32,-9},{-33,-10}};
        offset[FighterState::LK]={{13,5},{84,14},{239,13},{84,14},{13,5}};
        offset[FighterState::HK] = offset[FighterState::MK]={{-7,-32},{-54,-43},{-159,-8},{-76,-11},{-3,-39},{-45,-52}};
        //Crouch attack offset
        offset[FighterState::CrouchHP]=offset[FighterState::CrouchMP]=offset[FighterState::CrouchLP]={{-4,-39},{-1,-37},{-2,-38},{35,-44},{33,-44},{-5,-40},{-5,-39}};
        offset[FighterState::CrouchMK]=offset[FighterState::CrouchLK]={{-11,-43},{3,-44},{-8,-43}};
        offset[FighterState::CrouchHK]={{-22,-2},{-13,-14},{-9,-42}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-12,-4},{-30,-6}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{-9,18},{-54,16}};

        offset[FighterState::KnockDownL]=offset[FighterState::KnockDownM]=offset[FighterState::KnockDownH]={{-8,-4},{-56,-25},{-64,-36},{-121,-98}};
        offset[FighterState::GetUp]={{52,-76},{61,-59},{48,-50}};

        offset[FighterState::BackwardBlock]={{-22,0},{-53,-12}};
        offset[FighterState::CrouchBlock]={{-16,-45}};

        offset[FighterState::Win]={{11,3},{13,6},{8,5},{11,5}};
        offset[FighterState::WinStart]={{17,3}};

        offset[FighterState::TimeOverLoss]={{-74,3},{-123,20}};
        offset[FighterState::DefeatedLoss]={{-226,-83},{-203,-117},{-181,-87},{-251,-100},{-273,-105}};

        offset[FighterState::JumpUP]=offset[FighterState::JumpForward]={{0,0},{-15,3},{-39,16},{-17,7},{1,2}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
        offset[FighterState::JumpHP]=offset[FighterState::JumpMP]=offset[FighterState::JumpLP]={{-29,-2},{-40,-3},{-29,-2}};
        offset[FighterState::JumpLK]={{-43,14},{-15,2}};
        offset[FighterState::JumpMK]={{-122,27},{-45,16},{7,-15}};
        offset[FighterState::JumpHK]={{-135,15},{-62,-5},{-135,15}};
        offset[FighterState::JumpAttackEnd]={{-90,6}};
    }
    void Vega::LoadAllBox() {
        boxes.pushbox.size[FighterState::Idle]={120,250};
        boxes.pushbox.offset[FighterState::Idle]={-26,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={120,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={-26,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{160,125},{160,125},{160,125},{160,125}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{-9,115},{-16,111},{-21,102},{-13,110}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-33,43},{-33,45},{-28,42},{-28,42}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-14,-69},{-18,-70},{-26,-76},{-20,-73}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{100,100}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{160,75}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{8,65}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{-39,9}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{-12,-50}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{160,125},{160,75}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{5,104},{4,47}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{-33,48},{-44,-2}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-18,-56},{-6,-81}};

        std::vector<glm::vec2> reversedhurtbox = boxes.hurtbox.head.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.head.offset[FighterState::CrouchUp]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.body.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.body.offset[FighterState::CrouchUp]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.leg.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]=reversedhurtbox;

        //hurtbox Jump
        boxes.hurtbox.body.size[FighterState::JumpUP]={{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::JumpUP]={{100,150},{120,125},{140,125},{140,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::JumpUP]=boxes.hurtbox.head.offset[FighterState::JumpForward]={{26,115},{20,103},{-7,83},{17,107},{25,121}};
        boxes.hurtbox.body.offset[FighterState::JumpUP]=boxes.hurtbox.body.offset[FighterState::JumpForward]={{2,56},{-7,48},{-42,39},{-8,47},{3,58}};
        boxes.hurtbox.leg.offset[FighterState::JumpUP]=boxes.hurtbox.leg.offset[FighterState::JumpForward]={{-3,-35},{-4,-36},{-24,-22},{-2,-33},{-1,-47}};

        reversedhurtbox = boxes.hurtbox.head.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.head.offset[FighterState::JumpBackward]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.body.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.body.offset[FighterState::JumpBackward]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.leg.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.leg.offset[FighterState::JumpBackward]=reversedhurtbox;
    }
    void Vega::LoadSpecialMove() {

    }
}