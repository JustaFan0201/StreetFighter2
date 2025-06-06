//
// Created by asus on 2025/2/27.
//

#include "Fighters/Zangief.hpp"
namespace Util {
    Zangief::Zangief(): Fighter("Zangief") {
        LoadFighterData();
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/ussr.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/ussr_dark.png");
        country_position={{-244, 220},0,{1,1}};
        face_postion={{54, -253},0,{1,1}};
        BackgroundInit(8);
        StateInit();
        LoadCommonVelocities();
        Zangief::LoadAnimations();
        Zangief::LoadOffsetVelocity();
        Zangief::LoadAllBox();
        Zangief::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Zangief::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Zangief::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(4,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::JumpUP] = ActionInit(5, "JumpUp");
        animations[FighterState::JumpForward] = animations[FighterState::JumpUP];
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(3, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(4, "MP");
        animations[FighterState::HP] = ActionInit(7, "HP");
        animations[FighterState::LK] = ActionInit(3, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(3, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(3, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(3, "GetUp");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(2, "CrouchLP");
        animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");
        animations[FighterState::CrouchHP] = ActionInit(5, "CrouchHP");
        animations[FighterState::CrouchMP] = animations[FighterState::CrouchHP];
        animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK];
        animations[FighterState::CrouchHK] = animations[FighterState::CrouchLK];

        animations[FighterState::JumpMP] =animations[FighterState::JumpLP] = ActionInit(4, "JumpLP");
        animations[FighterState::JumpHP] = ActionInit(7, "JumpHP");
        animations[FighterState::JumpLK] = animations[FighterState::JumpMK] = animations[FighterState::JumpHK] = ActionInit(2, "JumpHK");

        animations[FighterState::JumpAttackEnd] = ActionInit(1, "JumpAttackEnd");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(2, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(3, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100, 150, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={90,120,150,120,90};
        frames[FighterState::JumpForward]=frames[FighterState::JumpUP];
        frames[FighterState::JumpBackward]=frames[FighterState::JumpUP];
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={40,40,40};
        frames[FighterState::CrouchUp]={40,40,40};
        frames[FighterState::LP]={60,120,90};
        frames[FighterState::MP]={60,90,150,60};
        frames[FighterState::HP]={60,90,180,90,90,60,30};
        frames[FighterState::LK]={60,90,120};
        frames[FighterState::MK]={60,90,150,90,60};
        frames[FighterState::HK]={90,210,120};

        frames[FighterState::CrouchLP]={120,150};
        frames[FighterState::CrouchMP]={60,90,150,90,60};
        frames[FighterState::CrouchHP]={60,90,180,120,90};
        frames[FighterState::CrouchLK]={60,120,90};
        frames[FighterState::CrouchMK]={90,150,90};
        frames[FighterState::CrouchHK]={120,180,120};

        frames[FighterState::HurtHeadL] = {90,90};
        frames[FighterState::HurtHeadM] = {160,160};
        frames[FighterState::HurtHeadH] = {210,210};
        frames[FighterState::HurtBodyL] = {90,90};
        frames[FighterState::HurtBodyM] = {160,160};
        frames[FighterState::HurtBodyH] = {210,210};

        frames[FighterState::KnockDownL] = {120,120,150};
        frames[FighterState::KnockDownM] = {140,140,170};
        frames[FighterState::KnockDownH] = {180,180,220};
        frames[FighterState::GetUp] = {150,150,150};

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(3, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(3, "GetUp");

        frames[FighterState::JumpLP]={60,60,240};
        frames[FighterState::JumpMP]={60,90,360};
        frames[FighterState::JumpHP]={90,120,480,120,90,60,60};
        frames[FighterState::JumpLK]={60,240};
        frames[FighterState::JumpMK]={90,360};
        frames[FighterState::JumpHK]={150,480};
        frames[FighterState::JumpAttackEnd]={100};

        frames[FighterState::BackwardBlock] = {60,60};
        frames[FighterState::CrouchBlock] = {60,60};

        frames[FighterState::WinStart]={180};
        frames[FighterState::Win]={180, 180};

        frames[FighterState::TimeOverLoss]={180,180,180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Zangief::LoadOffsetVelocity() {
        attacktype[FighterState::CrouchHK]=attacktype[FighterState::CrouchMK]=attacktype[FighterState::CrouchLK]=AttackType::Lower;

        offset[FighterState::Idle]={{{0,0},{-17,-1},{-25,-4},{-16,2}}};
        offset[FighterState::Crouch]={{-29,-47}};
        offset[FighterState::CrouchDown]={{-15,-10},{-25,-34},{-29,-47}};
        offset[FighterState::CrouchUp]={{-29,-47},{-25,-34},{-15,-10}};
        //Stand attack offset
        offset[FighterState::LP]={{0,-6},{38,-9},{1,-4}};;
        offset[FighterState::MP]={{16,1},{3,-6},{63,0},{10,-4}};
        offset[FighterState::HP]={{-23,2},{-6,-2},{49,-3},{35,-6},{49,-3},{6,0},{-28,6}};;
        offset[FighterState::LK]={{-46,8},{-16,11},{65,9}};
        offset[FighterState::MK]={{-44,9},{27,17},{115,5},{29,15},{-41,8}};
        offset[FighterState::HK]={{-15,10},{32,14},{-15,11}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{-22,-46},{30,-32}};
        offset[FighterState::CrouchLK]={{-6,-33},{66,-27},{-9,-33}};
        offset[FighterState::CrouchHP]={{-47,-36},{-30,-43},{16,-38},{-36,-41},{-48,-38}};
        offset[FighterState::CrouchMP]=offset[FighterState::CrouchHP];
        offset[FighterState::CrouchMK]=offset[FighterState::CrouchLK];
        offset[FighterState::CrouchHK]=offset[FighterState::CrouchLK];

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::KnockDownL]=offset[FighterState::KnockDownM]=offset[FighterState::KnockDownH]={{-121,-4},{-234,-24},{-326,-113}};
        offset[FighterState::GetUp]={{-144,-76},{-118,-60},{-91,-64}};

        offset[FighterState::BackwardBlock]={{-1,4},{-31,-2}};
        offset[FighterState::CrouchBlock]={{-33,-45},{-54,-58}};

        offset[FighterState::Win]={{4,10},{6,67}};
        offset[FighterState::WinStart]={{6,5}};

        offset[FighterState::TimeOverLoss]={{8,2},{5,2},{8,1}};
        offset[FighterState::DefeatedLoss]={{-103,19},{-323,-77},{-334,-105}};

        offset[FighterState::JumpForward]=offset[FighterState::JumpUP]={{29,30},{-23,30},{-50,21},{-23,30},{29,30}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
        offset[FighterState::JumpMP]=offset[FighterState::JumpLP]={{-151,20},{-105,44},{-15,15},{-90,0}};
        offset[FighterState::JumpHP]={{-151,20},{-105,44},{-15,15},{-90,0},{-15,15},{-105,44},{-151,20}};
        offset[FighterState::JumpLK]=offset[FighterState::JumpMK]=offset[FighterState::JumpHK]={{-128,28},{-115,13}};
        offset[FighterState::JumpAttackEnd]={{29,30}};
    }
    void Zangief::LoadAllBox() {

        boxes.pushbox.size[FighterState::Idle]={170,240};
        boxes.pushbox.offset[FighterState::Idle]={-30,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={160,140};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={-24,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{170,80},{170,80},{150,100},{170,80}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{180,160},{180,160},{180,160},{180,160}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{-2,132},{-2,128},{11,118},{-1,132}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-47,77},{-44,80},{-46,77},{-43,77}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-55,-48},{-52,-55},{-55,-53},{-49,-56}};

        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{180,70}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{180,100}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{16,81}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{5,24}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{-2,-50}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{170,100},{180,70},{180,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{180,130},{180,100},{180,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{4,120},{0,70},{-2,48}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{-17,55},{-16,17},{-3,-9}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-36,-62},{-22,-74},{-20,-83}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{180,70},{180,70},{170,100}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{180,100},{180,100},{180,130}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{13,83},{16,107},{21,155}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{2,29},{2,60},{-4,103}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{-3,-42},{-3,-25},{-14,-17}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{160,50},{160,30}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{180,100},{180,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{13,83},{-6,55}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{-3,31},{-8,23}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{-4,-45},{-12,-43}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{-2,135},{13,116}};
        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{100,80},{150,80}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{180,100},{160,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{43,80},{35,109}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-7,48},{16,51}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLP]={{8,-43},{15,-30}};

        boxes.hurtbox.head.size[FighterState::CrouchLK]=boxes.hurtbox.head.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]=boxes.hurtbox.body.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchHK]={{140,70},{140,60},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]=boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchHK]={{180,100},{200,100},{180,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]=boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchHK]={{-2,88},{3,73},{-7,91}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]=boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchHK]={{-25,35},{-9,25},{-29,34}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]=boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{-6,-42},{15,-60},{-7,-46}};

        boxes.hurtbox.head.size[FighterState::CrouchMP]=boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMP]=boxes.hurtbox.body.size[FighterState::CrouchHP]={{140,70},{100,100},{120,100},{100,100},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMP]=boxes.hurtbox.leg.size[FighterState::CrouchHP]={{180,110},{170,100},{150,100},{170,100},{180,110}};
        boxes.hurtbox.head.offset[FighterState::CrouchMP]=boxes.hurtbox.head.offset[FighterState::CrouchHP]={{11,95},{67,84},{92,100},{61,86},{9,93}};
        boxes.hurtbox.body.offset[FighterState::CrouchMP]=boxes.hurtbox.body.offset[FighterState::CrouchHP]={{0,39},{26,33},{77,58},{26,33},{0,39}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMP]=boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{17,-54},{24,-57},{29,-43},{24,-57},{17,-54}};
        //hurtbox Stand Attack
        boxes.hurtbox.body.size[FighterState::LP]={{140,80},{180,100},{140,80}};
        boxes.hurtbox.leg.size[FighterState::LP]={{210,160},{210,160},{210,160}};
        boxes.hurtbox.head.offset[FighterState::LP]={{54,129},{83,127},{53,131}};
        boxes.hurtbox.body.offset[FighterState::LP]={{2,73},{32,70},{3,73}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-9,-60},{4,-61},{-9,-60}};

        boxes.hurtbox.body.size[FighterState::MP]={{160,80},{180,80},{180,80},{150,80}};
        boxes.hurtbox.leg.size[FighterState::MP]={{200,170},{220,170},{220,170},{200,170}};
        boxes.hurtbox.head.offset[FighterState::MP]={{-30,134},{29,126},{59,130},{78,122}};
        boxes.hurtbox.body.offset[FighterState::MP]={{-30,78},{-22,73},{6,76},{19,66}};
        boxes.hurtbox.leg.offset[FighterState::MP]={{-23,-60},{-20,-65},{-15,-69},{8,-71}};

        boxes.hurtbox.body.size[FighterState::HP]={{160,80},{140,90},{140,80},{160,90},{140,80},{140,90},{160,80}};
        boxes.hurtbox.leg.size[FighterState::HP]={{190,170},{220,170},{220,160},{190,160},{220,160},{200,170},{190,170}};
        boxes.hurtbox.head.offset[FighterState::HP]={{5,134},{68,125},{120,123},{139,111},{119,124},{79,127},{3,135}};
        boxes.hurtbox.body.offset[FighterState::HP]={{2,76},{15,77},{59,72},{82,66},{59,72},{15,77},{2,76}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{10,-51},{19,-59},{35,-63},{44,-77},{35,-63},{19,-59},{10,-51}};
        //-----------------------------------------done---------------------------------------------------------------
        boxes.hurtbox.body.size[FighterState::LK]={{160,80},{140,90},{140,80}};
        boxes.hurtbox.leg.size[FighterState::LK]={{190,170},{150,170},{140,170}};
        boxes.hurtbox.head.offset[FighterState::LK]={{-22,139},{-12,138},{25,135}};
        boxes.hurtbox.body.offset[FighterState::LK]={{-27,81},{-15,83},{4,72}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{-7,-68},{33,-61},{85,-68}};

        boxes.hurtbox.leg.size[FighterState::MK]={{180,180},{160,180},{130,180},{160,180},{180,180}};
        boxes.hurtbox.head.offset[FighterState::MK]={{-23,142},{22,145},{58,132},{26,143},{-18,137}};
        boxes.hurtbox.body.offset[FighterState::MK]={{-30,77},{23,97},{35,84},{23,97},{-23,78}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{-11,-70},{69,-46},{92,-51},{73,-51},{-11,-71}};

        boxes.hurtbox.body.size[FighterState::HK]={{170,80},{170,80},{170,80}};
        boxes.hurtbox.leg.size[FighterState::HK]={{170,180},{150,180},{170,180}};
        boxes.hurtbox.head.offset[FighterState::HK]={{-8,135},{-52,135},{-9,136}};
        boxes.hurtbox.body.offset[FighterState::HK]={{-9,78},{-31,89},{-16,82}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{3,-62},{3,-58},{5,-60}};


        boxes.hurtbox.head.size[FighterState::JumpForward]=boxes.hurtbox.head.size[FighterState::JumpUP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::JumpForward]=boxes.hurtbox.body.size[FighterState::JumpUP]={{170,80},{170,80},{170,80},{150,100},{170,80}};
        boxes.hurtbox.leg.size[FighterState::JumpForward]=boxes.hurtbox.leg.size[FighterState::JumpUP]={{150,160},{170,160},{180,160},{170,160},{150,160}};
        boxes.hurtbox.head.offset[FighterState::JumpForward]=boxes.hurtbox.head.offset[FighterState::JumpUP]={{4,129},{-17,115},{-31,85},{-20,109},{6,131}};
        boxes.hurtbox.body.offset[FighterState::JumpForward]=boxes.hurtbox.body.offset[FighterState::JumpUP]={{-21,65},{-59,41},{-71,25},{-58,43},{-12,62}};
        boxes.hurtbox.leg.offset[FighterState::JumpForward]=boxes.hurtbox.leg.offset[FighterState::JumpUP]={{-53,-38},{-70,-40},{-69,-31},{-86,-38},{-64,-38}};

        std::vector<glm::vec2> reversedhurtbox = boxes.hurtbox.head.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.head.offset[FighterState::JumpBackward]=reversedhurtbox;

        std::vector<glm::vec2> reversedsize = boxes.hurtbox.body.size[FighterState::JumpForward];
        std::reverse(reversedsize.begin(), reversedsize.end());
        boxes.hurtbox.body.size[FighterState::JumpBackward]=reversedsize;

        reversedhurtbox = boxes.hurtbox.body.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.body.offset[FighterState::JumpBackward]=reversedhurtbox;

        reversedsize = boxes.hurtbox.leg.size[FighterState::JumpForward];
        std::reverse(reversedsize.begin(), reversedsize.end());
        boxes.hurtbox.leg.size[FighterState::JumpBackward]=reversedsize;

        reversedhurtbox = boxes.hurtbox.leg.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.leg.offset[FighterState::JumpBackward]=reversedhurtbox;

        boxes.hurtbox.body.size[FighterState::JumpMP]=boxes.hurtbox.body.size[FighterState::JumpLP]={{170,80},{170,80},{190,80},{140,120}};
        boxes.hurtbox.leg.size[FighterState::JumpMP]=boxes.hurtbox.leg.size[FighterState::JumpLP]={{180,160},{180,160},{180,160},{160,160}};
        boxes.hurtbox.head.offset[FighterState::JumpMP]=boxes.hurtbox.head.offset[FighterState::JumpLP]={{-1,97},{70,89},{114,83},{158,37}};
        boxes.hurtbox.body.offset[FighterState::JumpMP]=boxes.hurtbox.body.offset[FighterState::JumpLP]={{6,35},{40,28},{74,40},{91,33}};
        boxes.hurtbox.leg.offset[FighterState::JumpMP]=boxes.hurtbox.leg.offset[FighterState::JumpLP]={{27,-49},{35,-57},{47,-44},{45,-25}};

        boxes.hurtbox.body.size[FighterState::JumpHP]={{170,80},{170,80},{190,80},{140,120},{190,80},{170,80},{170,80}};
        boxes.hurtbox.leg.size[FighterState::JumpHP]={{180,160},{180,160},{180,160},{160,160},{180,160},{180,160},{180,160}};
        boxes.hurtbox.head.offset[FighterState::JumpHP]={{-1,97},{70,89},{114,83},{158,37},{114,83},{70,89},{-1,97}};
        boxes.hurtbox.body.offset[FighterState::JumpHP]={{6,35},{40,28},{74,40},{91,33},{74,40},{40,28},{6,35}};
        boxes.hurtbox.leg.offset[FighterState::JumpHP]={{27,-49},{35,-57},{47,-44},{45,-25},{47,-44},{35,-57},{27,-49}};

        boxes.hurtbox.body.size[FighterState::JumpMK]=boxes.hurtbox.body.size[FighterState::JumpLK]=boxes.hurtbox.body.size[FighterState::JumpHK]={{170,110},{150,160}};
        boxes.hurtbox.leg.size[FighterState::JumpMK]=boxes.hurtbox.leg.size[FighterState::JumpLK]=boxes.hurtbox.leg.size[FighterState::JumpHK]={{150,190},{260,110}};
        boxes.hurtbox.head.offset[FighterState::JumpMK]=boxes.hurtbox.head.offset[FighterState::JumpLK]=boxes.hurtbox.head.offset[FighterState::JumpHK]={{-116,108},{-134,4}};
        boxes.hurtbox.body.offset[FighterState::JumpMK]=boxes.hurtbox.body.offset[FighterState::JumpLK]=boxes.hurtbox.body.offset[FighterState::JumpHK]={{-58,64},{-70,-38}};
        boxes.hurtbox.leg.offset[FighterState::JumpMK]=boxes.hurtbox.leg.offset[FighterState::JumpLK]=boxes.hurtbox.leg.offset[FighterState::JumpHK]={{5,-19},{111,-61}};

        /*boxes.hurtbox.leg.size[FighterState::JumpAttackEnd]={{150,160}};
        boxes.hurtbox.head.offset[FighterState::JumpAttackEnd]={{40,181}};
        boxes.hurtbox.body.offset[FighterState::JumpAttackEnd]={{22,123}};
        boxes.hurtbox.leg.offset[FighterState::JumpAttackEnd]={{-20,-5}};*/
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={180,48};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{141,76},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchLK]=boxes.hitbox.size[FighterState::CrouchHK]=boxes.hitbox.size[FighterState::CrouchMK]={250,70};
        boxes.hitbox.offset[FighterState::CrouchLK]=boxes.hitbox.offset[FighterState::CrouchHK]=boxes.hitbox.offset[FighterState::CrouchMK]={{-1,-1},{160,-79},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]=boxes.hitbox.size[FighterState::CrouchMP]={130,60};
        boxes.hitbox.offset[FighterState::CrouchHP]=boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{182,75},{-1,-1},{-1,-1}};

        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={170,50};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{148,98},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={160,50};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{170,98},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={150,60};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{193,95},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={170,120};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{208,-60}};
        boxes.hitbox.size[FighterState::MK]={250,70};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{225,37},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={240,80};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{145,118},{-1,-1}};

        //hitbox Jump Attack
        boxes.hitbox.size[FighterState::JumpMP]=boxes.hitbox.size[FighterState::JumpLP]={210,70};
        boxes.hitbox.offset[FighterState::JumpMP]=boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{-1,-1},{218,38},{-1,-1}};
        boxes.hitbox.size[FighterState::JumpHP]={210,70};
        boxes.hitbox.offset[FighterState::JumpHP]={{-1,-1},{-1,-1},{218,38},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::JumpMK]=boxes.hitbox.size[FighterState::JumpLK]=boxes.hitbox.size[FighterState::JumpHK]={320,90};
        boxes.hitbox.offset[FighterState::JumpMK]=boxes.hitbox.offset[FighterState::JumpLK]=boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{110,-61}};
    }
    void Zangief::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(9, "Special_1");
        offset[FighterState::Special_1]={{-61,11},{-62,7},{-42,4},{-92,5},{-152,6},{-72,7},{-67,1},{-109,5},{-158,8}};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LP]={90,90,120,90,120,90,120,90,120};
        boxes.hurtbox.body.size[FighterState::Special_1]={{170,80},{150,80},{150,80},{150,80},{170,80},{150,80},{150,80},{150,80},{170,80}};
        boxes.hurtbox.leg.size[FighterState::Special_1]={{180,160},{150,160},{150,160},{100,160},{150,160},{150,160},{150,160},{100,160},{150,160}};
        boxes.hurtbox.head.offset[FighterState::Special_1]={{61,139},{42,136},{-7,134},{-44,135},{-64,135},{32,136},{-31,133},{-62,137},{-73,138}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{48,75},{0,69},{-35,64},{-35,66},{-75,66},{-13,66},{-61,65},{-50,68},{-76,68}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{38,-61},{3,-58},{-12,-67},{-21,-61},{-69,-68},{-8,-63},{-33,-75},{-41,-65},{-73,-69}};

        boxes.hitbox.size[FighterState::Special_1]={380,100};
        boxes.hitbox.offset[FighterState::Special_1]={{-1,-1},{-1,-1},{14,78},{-1,-1},{-88,82},{-1,-1},{14,78},{-1,-1},{-88,82}};

        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::LP]={4,0};
        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::LP]=10;
        SpecialMoveData.attackdata[FighterState::Special_1].HitStrength[Keys::LP]=HitStrength::SP;

        StateEnter[FighterState::Special_1]=[this] { DoubleLariatStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { DoubleLariatStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Zangief/SP1.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={};
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ALL_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Null;
        SpecificStates.borderCheckStates.insert(FighterState::Special_1);
        SpecificStates.InvincibleForFlyObj.insert(FighterState::Special_1);

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Zangief/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Zangief/Loss.wav");
        SpecialMoveData.SkillCommand[FighterState::Special_1].SpecialNumer=SpecialNumer::Special_1;

        SpecificStates.SpecialStates.insert(FighterState::Special_1);

        SpecificStates.SpecialAttackStates.insert(FighterState::Special_1);
    }
    void Zangief::DoubleLariatStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Zangief::DoubleLariatStateUpdate() {
        if(controller->IsForward(direction)) {
            velocity=GetInitialvelocity();
        }
        else if(controller->IsBackward(direction)) {
            velocity=glm::vec2{-1,1}* GetInitialvelocity();
        }
        else{
            ResetVelocity();
        }
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
}