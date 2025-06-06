//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ryu.hpp"
namespace Util {
    Ryu::Ryu(): Fighter("Ryu") {
        LoadFighterData();
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/japan.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/japan_dark.png");
        country_position={{14,90},0,{1,1}};
        face_postion={{-160, -150},0,{1,1}};
        BackgroundInit(15);
        StateInit();
        LoadCommonVelocities();
        Ryu::LoadAnimations();
        Ryu::LoadOffsetVelocity();
        Ryu::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Ryu::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Ryu::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(5,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::JumpUP] = ActionInit(7, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(6, "JumpForward");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(2, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;

        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::HP] = ActionInit(6, "HP");
        animations[FighterState::LK] = ActionInit(4, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");

        animations[FighterState::CrouchLP] = ActionInit(3, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(5, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(5, "CrouchHP");
        animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");
        animations[FighterState::CrouchMK] = ActionInit(5, "CrouchMK");
        animations[FighterState::CrouchHK] = ActionInit(5, "CrouchHK");

        animations[FighterState::JumpLP] = ActionInit(2, "JumpLP");
        animations[FighterState::JumpMP] = ActionInit(3, "JumpMP");
        animations[FighterState::JumpHP] = ActionInit(3, "JumpHP");
        animations[FighterState::JumpLK] = ActionInit(2, "JumpLK");
        animations[FighterState::JumpMK] = ActionInit(3, "JumpMK");
        animations[FighterState::JumpHK] = ActionInit(5, "JumpHK");
        animations[FighterState::JumpAttackEnd] = ActionInit(2, "JumpAttackEnd");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(5, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(4, "GetUp");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::WinStart]=ActionInit(3, "WinStart");
        animations[FighterState::Win]=ActionInit(2, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(1, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(6, "DefeatedLoss");

        frames[FighterState::Idle]={100, 150, 200, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,90,120,150,120,90,60};
        frames[FighterState::JumpForward]={60,90,120,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,120,90,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60};
        frames[FighterState::CrouchUp]={60,60};

        frames[FighterState::LP]={60,60,90};
        frames[FighterState::MP]={30,60,120,60,30};
        frames[FighterState::HP]={60,90,180,90,60,60};
        frames[FighterState::LK]={30,30,90,60};
        frames[FighterState::MK]={30,60,120,60,30};
        frames[FighterState::HK]={60,90,180,90,90};

        frames[FighterState::CrouchLP]={60,90,60};
        frames[FighterState::CrouchMP]={30,60,120,60,30};
        frames[FighterState::CrouchHP]={60,90,180,90,60};
        frames[FighterState::CrouchLK]={60,90,60};
        frames[FighterState::CrouchMK]={30,60,120,60,30};
        frames[FighterState::CrouchHK]={60,180,120,90,60};

        frames[FighterState::JumpLP]={60,240};
        frames[FighterState::JumpMP]={60,60,360};
        frames[FighterState::JumpHP]={90,90,480};
        frames[FighterState::JumpLK]={60,240};
        frames[FighterState::JumpMK]={60,60,360};
        frames[FighterState::JumpHK]={90,90,480,90,90};
        frames[FighterState::JumpAttackEnd]={120,90};

        frames[FighterState::HurtHeadL] = {90,90};
        frames[FighterState::HurtHeadM] = {160,160};
        frames[FighterState::HurtHeadH] = {210,210};
        frames[FighterState::HurtBodyL] = {90,90};
        frames[FighterState::HurtBodyM] = {160,160};
        frames[FighterState::HurtBodyH] = {210,210};

        frames[FighterState::KnockDownL] = {60,75,120,75,60};
        frames[FighterState::KnockDownM] = {75,90,120,90,75};
        frames[FighterState::KnockDownH] = {90,120,180,120,90};
        frames[FighterState::GetUp] = {120,120,120,90};

        frames[FighterState::BackwardBlock] = {60,60};
        frames[FighterState::CrouchBlock] = {60,60};

        frames[FighterState::WinStart]={180,180,180};
        frames[FighterState::Win]={180};

        frames[FighterState::TimeOverLoss]={180};
        frames[FighterState::DefeatedLoss]={180,180,180,180,180,180};
    }
    void Ryu::LoadOffsetVelocity() {
        attacktype[FighterState::CrouchLK]=attacktype[FighterState::CrouchMK]=AttackType::Lower;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Crouch]={{35,-43}};
        offset[FighterState::CrouchDown]={{10,-9},{31,-30}};
        offset[FighterState::CrouchUp]={{31,-30},{10,-9}};
        //Stand attack offset
        offset[FighterState::LP]={{5,3},{44,2},{3,3}};
        offset[FighterState::MP]={{14,5},{-9,5},{56,5},{-10,6},{15,6}};
        offset[FighterState::HP]={{15,5},{23,5},{67,5},{40,34},{23,6},{15,5}};
        offset[FighterState::LK]={{15,6},{64,4},{140,4},{64,5}};
        offset[FighterState::MK]={{20,12},{-25,10},{-25,10},{-27,9},{23,11}};
        offset[FighterState::HK]={{32,5},{45,12},{68,11},{44,-11},{3,-9}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{42,-43},{85,-44},{46,-44}};
        offset[FighterState::CrouchMP]={{38,-42},{43,-42},{85,-42},{42,-42},{39,-43}};
        offset[FighterState::CrouchHP]={{34,-28},{59,-2},{51,53},{58,-2},{37,-29}};
        offset[FighterState::CrouchLK]={{38,-42},{107,-43},{37,-43}};
        offset[FighterState::CrouchMK]={{39,-42},{-15,-49},{-17,-52},{-14,-49},{37,-44}};
        offset[FighterState::CrouchHK]={{68,-45},{115,-46},{76,-48},{17,-45},{11,-42}};

        offset[FighterState::JumpUP]={{8,-3},{-2,25},{-12,26},{14,17},{2,8},{-16,11},{-5,32}};
        offset[FighterState::JumpForward]={{12,26},{15,17},{6,-19},{29,-20},{9,1},{-3,31}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
        offset[FighterState::JumpLP]={{0,0},{27,-2}};
        offset[FighterState::JumpMP]={{20,19},{6,20},{6,17}};
        offset[FighterState::JumpHP]={{2,9},{-26,18},{36,11}};
        offset[FighterState::JumpLK]={{-14,28},{-28,31}};
        offset[FighterState::JumpMK]={{-19,10},{-81,-7},{14,-15}};
        offset[FighterState::JumpHK]={{-17,27},{-4,35},{48,48},{-39,39},{-111,29}};
        offset[FighterState::JumpAttackEnd]={{-16,11},{-5,32}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::KnockDownL]=offset[FighterState::KnockDownM]=offset[FighterState::KnockDownH]={{-29,20},{-38,12},{-31,-15},{-58,-61},{-15,-83}};
        offset[FighterState::GetUp]={{11,-28},{-8,41},{-63,10},{9,20}};

        offset[FighterState::BackwardBlock]={{-3,3},{1,5}};
        offset[FighterState::CrouchBlock]={{35,-44},{16,-38}};

        offset[FighterState::Win]={{5,6},{7,7}};
        offset[FighterState::WinStart]={{8,12},{7,6},{5,7}};

        offset[FighterState::TimeOverLoss]={{8,10}};
        offset[FighterState::DefeatedLoss]={{-142,-15},{-149,-61},{-210,-67},{-196,-73},{-193,-73},{-206,-93}};
    }
    void Ryu::LoadAllBox() {
        boxes.pushbox.size[FighterState::Idle]={100,200};
        boxes.pushbox.offset[FighterState::Idle]={15,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={100,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={15,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{100,125},{100,125},{100,125},{100,125},{100,125},};
        boxes.hurtbox.head.offset[FighterState::Idle]={{23,113},{28,110},{27,109},{26,117},{25,116},{25,116}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-15,57},{-15,57},{-10,55},{-10,54},{-12,53},{-12,53}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-12,-53},{-12,-52},{-12,-52},{-12,-52},{-11,-48},{-11,-48}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{100,50}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{100,50}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{28,66}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{-1,18}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{10,-49}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{100,125},{100,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{6,119},{22,80}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{-19,78},{-4,28}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-25,-25},{10,-49}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{100,50},{100,125}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{22,80},{6,119}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{-4,28},{-19,78}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{10,-49},{-25,-25}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{100,50},{100,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{11,67},{-32,74}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{4,10},{-25,27}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{11,-45},{-8,-44}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{-5,113},{-21,111}};
        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{29,66},{42,63},{34,64}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-9,14},{5,13},{-3,11}};

        boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]={{120,70},{100,70},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]={{14,71},{5,71},{12,71}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-16,17},{-7,18},{-15,18}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{20,-52},{20,-57},{22,-50}};

        boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMP]={{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMP]={{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMP]={{38,63},{44,66},{42,69},{43,66},{39,66}};
        boxes.hurtbox.body.offset[FighterState::CrouchMP]={{1,13},{9,13},{5,19},{4,16},{4,16}};

        boxes.hurtbox.head.size[FighterState::CrouchMK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMK]={{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMK]={{120,70},{150,70},{120,70},{150,70},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMK]={{15,71},{-120,59},{-148,43},{-118,58},{11,68}};
        boxes.hurtbox.body.offset[FighterState::CrouchMK]={{-19,20},{-116,13},{-143,0},{-114,14},{-21,18}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]={{16,-55},{-81,-57},{-80,-58},{-60,-58},{12,-57}};

        boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]={{100,70},{100,100},{100,100},{100,100},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]={{100,70},{100,125},{100,125},{100,125},{100,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]={{13,86},{30,143},{46,167},{32,143},{16,86}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]={{-22,32},{10,78},{58,92},{11,74},{-17,25}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{3,-44},{17,-30},{38,-24},{14,-33},{14,-48}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]={{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]={{100,50},{100,50},{120,50},{120,50},{120,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]={{8,66},{5,66},{-26,66},{-66,66},{-39,69}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]={{-23,9},{-23,15},{-11,15},{-36,17},{-55,22}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{-9,-46},{0,-48},{16,-48},{-64,-53},{-53,-41}};
        //hurtbox Stand Attack
        boxes.hurtbox.head.offset[FighterState::HP]={{49,111},{74,111},{65,114},{49,127},{50,113}};
        boxes.hurtbox.body.offset[FighterState::HP]={{23,51},{47,48},{57,53},{52,56},{11,49},{19,46}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{8,-63},{23,-66},{34,-68},{21,-65},{-3,-70},{5,-62}};

        boxes.hurtbox.head.offset[FighterState::LK]={{8,115},{58,114},{80,113},{57,113}};
        boxes.hurtbox.body.offset[FighterState::LK]={{-9,44},{26,43},{66,45},{29,46}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{-17,-66},{54,-49},{74,-58},{56,-57}};

        boxes.hurtbox.head.offset[FighterState::MK]={{11,111},{-53,110},{-152,106},{-55,111},{15,112}};
        boxes.hurtbox.body.offset[FighterState::MK]={{-11,41},{-50,48},{-120,50},{-52,51},{-6,45}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{-16,-68},{-46,-58},{-62,-59},{-60,-58},{-16,-61}};

        boxes.hurtbox.head.offset[FighterState::HK]={{-65,51},{-95,52},{-113,63},{-112,75},{-101,88}};
        boxes.hurtbox.body.offset[FighterState::HK]={{25,37},{-18,31},{-41,30},{-54,39},{-56,35}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{59,-56},{44,-55},{24,-52},{17,-53},{-4,-62}};
        //hurtbox Jump
        boxes.hurtbox.head.offset[FighterState::JumpUP]={{31,100},{-14,148},{-13,135},{26,109},{36,85},{-11,113},{-13,141}};
        boxes.hurtbox.body.offset[FighterState::JumpUP]={{-4,43},{-19,76},{-31,64},{-8,53},{-8,29},{-28,47},{-18,74}};
        boxes.hurtbox.leg.offset[FighterState::JumpUP]={{2,-55},{-4,-18},{-19,-13},{7,-28},{-2,-39},{-28,-36},{-21,-18}};

        boxes.hurtbox.body.size[FighterState::JumpForward]={{100,100},{100,100},{120,100},{120,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::JumpForward]={{120,150},{100,125},{120,80},{120,80},{100,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::JumpForward]={{-3,124},{62,76},{115,-86},{-135,-79},{-83,78},{-15,112}};
        boxes.hurtbox.body.offset[FighterState::JumpForward]={{-25,53},{-2,54},{60,-38},{-37,-69},{-32,30},{-19,38}};
        boxes.hurtbox.leg.offset[FighterState::JumpForward]={{-11,-38},{-2,-42},{-61,-47},{92,-21},{42,-55},{-23,-63}};

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

        boxes.hurtbox.head.offset[FighterState::JumpLP]={{-2,73},{0,76}};
        boxes.hurtbox.body.offset[FighterState::JumpLP]={{-42,22},{-42,23}};
        boxes.hurtbox.leg.offset[FighterState::JumpLP]={{-46,-50},{-49,-44}};

        boxes.hurtbox.leg.size[FighterState::JumpMP]={{100,125},{100,125},{140,75}};
        boxes.hurtbox.head.offset[FighterState::JumpMP]={{56,88},{43,88},{46,71}};
        boxes.hurtbox.body.offset[FighterState::JumpMP]={{5,42},{-1,39},{-9,24}};
        boxes.hurtbox.leg.offset[FighterState::JumpMP]={{-11,-42},{-22,-38},{-21,-46}};

        boxes.hurtbox.head.offset[FighterState::JumpHP]={{41,76},{-23,97},{44,57}};
        boxes.hurtbox.body.offset[FighterState::JumpHP]={{-5,20},{-32,39},{-6,5}};
        boxes.hurtbox.leg.offset[FighterState::JumpHP]={{-6,-49},{-23,-43},{-1,-54}};

        boxes.hurtbox.leg.size[FighterState::JumpLK]={{100,125},{75,140}};
        boxes.hurtbox.head.offset[FighterState::JumpLK]={{12,106},{-15,115}};
        boxes.hurtbox.body.offset[FighterState::JumpLK]={{-12,42},{-40,61}};
        boxes.hurtbox.leg.offset[FighterState::JumpLK]={{4,-48},{-36,-42}};

        boxes.hurtbox.leg.size[FighterState::JumpMK]={{100,125},{100,125},{125,60}};
        boxes.hurtbox.head.offset[FighterState::JumpMK]={{58,89},{-24,64},{-10,31}};
        boxes.hurtbox.body.offset[FighterState::JumpMK]={{6,38},{-73,25},{-40,-16}};
        boxes.hurtbox.leg.offset[FighterState::JumpMK]={{-8,-40},{-63,-51},{-31,-75}};

        boxes.hurtbox.leg.size[FighterState::JumpMK]={{100,125},{80,125},{80,140},{80,140},{100,125}};
        boxes.hurtbox.head.offset[FighterState::JumpHK]={{-6,129},{8,92},{15,128},{-38,123},{-113,92}};
        boxes.hurtbox.body.offset[FighterState::JumpHK]={{-8,63},{-12,29},{-11,75},{-53,63},{-117,35}};
        boxes.hurtbox.leg.offset[FighterState::JumpHK]={{3,-50},{7,-59},{-2,-26},{-32,-20},{-96,-53}};

        boxes.hurtbox.head.offset[FighterState::JumpAttackEnd]={{0,103},{-3,131}};
        boxes.hurtbox.body.offset[FighterState::JumpAttackEnd]={{-18,37},{-8,64}};
        boxes.hurtbox.leg.offset[FighterState::JumpAttackEnd]={{-18,-46},{-11,-38}};

        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={100,50};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{133,36},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMP]={140,50};
        boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{121,44},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]={50,100};
        boxes.hitbox.offset[FighterState::CrouchHP]={{-1,-1},{-1,-1},{81,205},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchLK]={150,60};
        boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{141,-63},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMK]={150,80};
        boxes.hitbox.offset[FighterState::CrouchMK]={{-1,-1},{-1,-1},{60,-61},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHK]={150,80};
        boxes.hitbox.offset[FighterState::CrouchHK]={{-1,-1},{130,-49},{-1,-1},{-1,-1},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={100,50};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{110,78},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={140,50};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{125,79},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={50,100};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{-1,-1},{130,142},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={150,80};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{150,-20},{-1,-1}};
        boxes.hitbox.size[FighterState::MK]={100,100};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{56,99},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={120,100};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{-1,-1},{152,102},{-1,-1},{-1,-1}};
        //hitbox Jump Attack
        boxes.hitbox.size[FighterState::JumpLP]={100,80};
        boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{99,4}};
        boxes.hitbox.size[FighterState::JumpMP]={100,150};
        boxes.hitbox.offset[FighterState::JumpMP]={{-1,-1},{-1,-1},{85,-31}};
        boxes.hitbox.size[FighterState::JumpHP]={120,80};
        boxes.hitbox.offset[FighterState::JumpHP]={{-1,-1},{-1,-1},{98,3}};
        boxes.hitbox.size[FighterState::JumpLK]={100,80};
        boxes.hitbox.offset[FighterState::JumpLK]={{-1,-1},{54,99}};
        boxes.hitbox.size[FighterState::JumpMK]={170,80};
        boxes.hitbox.offset[FighterState::JumpMK]={{-1,-1},{-1,-1},{104,-89}};
        boxes.hitbox.size[FighterState::JumpHK]={180,60};
        boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{-1,-1},{112,27},{-1,-1},{-1,-1}};
    }
    void Ryu::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(4, "Special_1");
        offset[FighterState::Special_1]={{-23,1},{-23,-11},{-31,-9},{-12,-19}};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LP]={90,90,150,360};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::MP]={90,90,180,480};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::HP]={90,90,210,600};

        boxes.hurtbox.leg.size[FighterState::Special_1]={{150,100},{200,100},{200,100},{200,100}};
        boxes.hurtbox.head.offset[FighterState::Special_1]={{-12,111},{-31,89},{-1,80},{72,72}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{-25,53},{-49,34},{-23,27},{39,21}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{-13,-62},{-26,-73},{-16,-76},{12,-78}};

        StateEnter[FighterState::Special_1]=[this] { HandoukenStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { HandoukenStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/SP1.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={
            SpecialMoveDirection::Forward,
            SpecialMoveDirection::Forward_down,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ANY_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Command;

        animations[FighterState::Special_2]=ActionInit(6, "Special_2");
        offset[FighterState::Special_2]={{35,-3},{53,-4},{104,72},{47,57},{17,42},{0,24}};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::LP]={2,6};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::MP]={3,7};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::HP]={4,8};

        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LP]={60,120,240,120,90,60};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::MP]={60,120,320,180,120,90};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::HP]={60,120,400,240,160,90};

        boxes.hurtbox.leg.size[FighterState::Special_2]={{150,100},{120,100},{100,150},{100,150},{100,100},{120,100}};
        boxes.hurtbox.head.offset[FighterState::Special_2]={{40,79},{41,110},{72,155},{17,156},{-16,132},{-33,116}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{11,22},{11,42},{82,91},{42,84},{-23,66},{-38,61}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{13,-64},{16,-58},{81,-2},{47,-17},{-15,-48},{-28,-53}};

        boxes.hitbox.size[FighterState::Special_2]={80,250};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{106,123},{-1,-1},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LP]=10;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::MP]=15;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::HP]=22;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LP]=HitStrength::SP;
        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::MP]=HitStrength::SP;
        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::HP]=HitStrength::SP;

        StateEnter[FighterState::Special_2]=[this] { ShoryukenStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { ShoryukenStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/SP2.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_2].command={
            SpecialMoveDirection::down,
            SpecialMoveDirection::Forward_down,
            SpecialMoveDirection::Forward
        };
        SpecialMoveData.SkillCommand[FighterState::Special_2].requiredAttack=AttackButton::ANY_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_2].commandtype=CommandType::Command;
        SpecificStates.borderCheckStates.insert(FighterState::Special_2);

        animations[FighterState::Special_3]=ActionInit(10, "Special_3");
        offset[FighterState::Special_3]={{104,23},{83,9},{24,39},{161,44},{34,44},{-10,44},{111,39},{161,44},{99,30},{30,6}};
        SpecialMoveData.animationData[FighterState::Special_3].initialvelocitys[Keys::LK]={9,0};
        SpecialMoveData.animationData[FighterState::Special_3].initialvelocitys[Keys::MK]={11,0};
        SpecialMoveData.animationData[FighterState::Special_3].initialvelocitys[Keys::HK]={13,0};

        SpecialMoveData.animationData[FighterState::Special_3].frames[Keys::LK]={30,60,90,90,60,90,60,90,120,90};
        SpecialMoveData.animationData[FighterState::Special_3].frames[Keys::MK]={30,60,90,120,60,120,60,120,150,120};
        SpecialMoveData.animationData[FighterState::Special_3].frames[Keys::HK]={30,60,90,150,60,150,60,150,180,120};

        boxes.hurtbox.leg.size[FighterState::Special_3]={{100,150},{100,100},{100,50},{50,150},{100,150},{50,150},{50,150},{50,150},{100,150},{100,150}};
        boxes.hurtbox.head.offset[FighterState::Special_3]={{-13,133},{-13,88},{-115,92},{7,139},{-79,132},{-75,133},{-4,134},{7,139},{9,119},{-79,92}};
        boxes.hurtbox.body.offset[FighterState::Special_3]={{-15,64},{-11,24},{-64,37},{-17,74},{-77,75},{-38,70},{-8,73},{-17,74},{-16,58},{-72,38}};
        boxes.hurtbox.leg.offset[FighterState::Special_3]={{2,-46},{1,-66},{-70,-31},{-16,-45},{-64,-15},{-52,-10},{-32,-25},{-16,-45},{3,-32},{-72,-62}};

        boxes.hitbox.size[FighterState::Special_3]={250,80};
        boxes.hitbox.offset[FighterState::Special_3]={{-1,-1},{-1,-1},{-1,-1},{76,29},{-1,-1},{-155,27},{-1,-1},{76,29},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_3].attack[Keys::LK]=8;
        SpecialMoveData.attackdata[FighterState::Special_3].attack[Keys::MK]=12;
        SpecialMoveData.attackdata[FighterState::Special_3].attack[Keys::HK]=15;

        SpecialMoveData.attackdata[FighterState::Special_3].HitStrength[Keys::LK]=HitStrength::L;
        SpecialMoveData.attackdata[FighterState::Special_3].HitStrength[Keys::MK]=HitStrength::M;
        SpecialMoveData.attackdata[FighterState::Special_3].HitStrength[Keys::HK]=HitStrength::H;

        StateEnter[FighterState::Special_3]=[this] { TatsumakiSenpuStateEnter(); };
        StateUpdate[FighterState::Special_3]=[this] { TatsumakiSenpuStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_3].sound[Keys::LK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/SP3_L.wav");
        SpecialMoveData.sounddata[FighterState::Special_3].sound[Keys::MK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/SP3_M.wav");
        SpecialMoveData.sounddata[FighterState::Special_3].sound[Keys::HK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/SP3_H.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_3].command={
            SpecialMoveDirection::Backward,
            SpecialMoveDirection::Backward_down,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_3].requiredAttack=AttackButton::ANY_KICK;
        SpecialMoveData.SkillCommand[FighterState::Special_3].commandtype=CommandType::Command;
        SpecificStates.borderCheckStates.insert(FighterState::Special_3);
        SpecificStates.InvincibleForFlyObj.insert(FighterState::Special_3);

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Ryu/Loss.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].SpecialNumer=SpecialNumer::Special_1;
        SpecialMoveData.SkillCommand[FighterState::Special_2].SpecialNumer=SpecialNumer::Special_2;
        SpecialMoveData.SkillCommand[FighterState::Special_3].SpecialNumer=SpecialNumer::Special_3;

        SpecificStates.SpecialStates.insert(FighterState::Special_1);
        SpecificStates.SpecialStates.insert(FighterState::Special_2);
        SpecificStates.SpecialStates.insert(FighterState::Special_3);

        SpecificStates.SpecialAttackStates.insert(FighterState::Special_2);
        SpecificStates.SpecialAttackStates.insert(FighterState::Special_3);
    }
    void Ryu::HandoukenStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Ryu::HandoukenStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex()==3){AddFlyingObject(FlyingObjectType::FireBall,ButtonType);ClearButtonType();}
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }

    void Ryu::ShoryukenStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        velocity=GetInitialvelocity();
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Ryu::ShoryukenStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex() <= 2) {
            velocity.x += velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
            velocity.y += velocity.y * 0.05f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else {
            velocity.y += Gravity * Time::GetDeltaTimeMs() / 1000.0f;
        }
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }
    void Ryu::TatsumakiSenpuStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        velocity=GetInitialvelocity();
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Ryu::TatsumakiSenpuStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex() <= 5) {
            velocity.x += velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else if (ActionNow->GetCurrentFrameIndex() <= 7) {
            velocity.x -= velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else {
            ResetVelocity();
        }
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
}