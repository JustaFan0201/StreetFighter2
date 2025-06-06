//
// Created by asus on 2025/2/27.
//

#include "Fighters/Blanka.hpp"
namespace Util {
    Blanka::Blanka(): Fighter("Blanka") {
        LoadFighterData();
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/brazil.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/brazil_dark.png");
        country_position={{323, 23},0,{1,1}};
        face_postion={{54, -150},0,{1,1}};
        BackgroundInit(4);
        StateInit();
        LoadCommonVelocities();
        Blanka::LoadAnimations();
        Blanka::LoadOffsetVelocity();
        Blanka::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Blanka::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Blanka::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(3,"Idle");
        animations[FighterState::Backward] = ActionInit(8,"Backward");
        animations[FighterState::Forward] = ActionInit(8,"Forward");
        animations[FighterState::JumpUP] = ActionInit(8, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(6, "JumpForward");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(2, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;
        animations[FighterState::LP] = ActionInit(6, "LP");
        animations[FighterState::MP] = ActionInit(4, "MP");
        animations[FighterState::HP] = ActionInit(6, "HP");
        animations[FighterState::LK] = ActionInit(6, "LK");
        animations[FighterState::MK] = ActionInit(6, "MK");
        animations[FighterState::HK] = ActionInit(7, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(4, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(4, "HurtBody");

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(5, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(4, "GetUp");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(6, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(8, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(6, "CrouchHP");
        animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");
        animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK];
        animations[FighterState::CrouchHK] = ActionInit(6, "CrouchHK");

        animations[FighterState::JumpMP] = animations[FighterState::JumpLP] = ActionInit(5, "JumpLP");
        animations[FighterState::JumpHP] = ActionInit(4, "JumpHP");
        animations[FighterState::JumpMK] = animations[FighterState::JumpLK] = ActionInit(3, "JumpLK");
        animations[FighterState::JumpHK] = ActionInit(5, "JumpHK");
        animations[FighterState::JumpAttackEnd] = ActionInit(1, "JumpAttackEnd");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(2, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(1, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={150, 150, 150};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,90,90,90,120,90,90,90,60};
        frames[FighterState::JumpForward]={60,90,120,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,120,90,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60};
        frames[FighterState::CrouchUp]={60,60};
        frames[FighterState::LP]={30,90,60,60,30,30};
        frames[FighterState::MP]={60,90,150,90};
        frames[FighterState::HP]={60,180,90,60,60,30};
        frames[FighterState::LK]={30,60,90,30,30,30};
        frames[FighterState::MK]={60,90,150,90,60,60};
        frames[FighterState::HK]={60,210,120,90,60,60,30};

        frames[FighterState::CrouchLP]={30,90,60,60,60,30};
        frames[FighterState::CrouchMP]={30,60,120,90,60,60,60,30};
        frames[FighterState::CrouchHP]={60,60,180,60,120,60};
        frames[FighterState::CrouchLK]={90,90,120};
        frames[FighterState::CrouchMK]={90,120,180};
        frames[FighterState::CrouchHK]={60,90,210,120,90,60};

        frames[FighterState::JumpLP]={60,60,240,60,60};
        frames[FighterState::JumpMP]={60,90,360,90,60};
        frames[FighterState::JumpHP]={180,480,90,90};
        frames[FighterState::JumpLK]={60,60,240};
        frames[FighterState::JumpMK]={60,90,360};
        frames[FighterState::JumpHK]={90,90,480,90,90};
        frames[FighterState::JumpAttackEnd]={120};

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

        frames[FighterState::WinStart]={180};
        frames[FighterState::Win]={180, 180};

        frames[FighterState::TimeOverLoss]={180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Blanka::LoadOffsetVelocity() {
        attacktype[FighterState::CrouchHK]=attacktype[FighterState::CrouchMK]=attacktype[FighterState::CrouchLK]=AttackType::Lower;
        offset[FighterState::Idle]={{0,0},{0,0},{0,0}};
        offset[FighterState::Forward]={{0,-20},{0,-20},{0,-20},{0,-20},{0,-20},{0,-20},{0,-20},{0,-20}};
        offset[FighterState::Crouch]={{-13,-52}};
        offset[FighterState::CrouchDown]={{-9,-16},{-14,-40}};
        offset[FighterState::CrouchUp]={{-14,-40},{-9,-16}};
        //Stand attack offset
        offset[FighterState::LP]={{1,-5},{63,0},{29,0},{27,0},{64,1},{3,-3}};
        offset[FighterState::MP]={{-4,52},{39,19},{57,1},{21,-4}};
        offset[FighterState::HP]={{16,-5},{55,-1},{8,32},{7,32},{54,1},{18,-6}};
        offset[FighterState::LK]={{-27,-1},{-8,-3},{47,-10},{47,-10},{-11,-8},{-37,-4}};
        offset[FighterState::MK]={{-17,5},{-11,3},{65,5},{65,5},{-5,1},{-11,2}};
        offset[FighterState::HK]={{33,-9},{24,-12},{27,1},{-52,59},{-93,25},{-1,3},{-7,-13}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{32,-58},{106,-66},{88,-65},{91,-66},{105,-67},{29,-56}};
        offset[FighterState::CrouchMP]={{-67,-58},{82,-69},{98,-54},{95,-51},{95,-51},{98,-55},{86,-68},{-68,-59}};
        offset[FighterState::CrouchHP]={{0,-56},{23,-62},{128,-18},{125,-20},{23,-60},{0,-57}};
        offset[FighterState::CrouchLK]={{35,-37},{76,-49},{163,-21}};
        offset[FighterState::CrouchMK]={{35,-37},{76,-49},{163,-21}};
        offset[FighterState::CrouchHK]={{3,-2},{65,-8},{142,-17},{143,-19},{56,-6},{14,-1}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-65,7},{-98,5},{-125,-15},{-68,-17}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{-13,-18},{-31,-26},{-55,-35},{-10,-11}};

        offset[FighterState::KnockDownL]=offset[FighterState::KnockDownM]=offset[FighterState::KnockDownH]={{-57,-14},{-98,-66},{-125,-77},{-75,-83},{-69,-89}};
        offset[FighterState::GetUp]={{-228,-99},{-23,-7},{-38,-3},{-133,-15}};

        offset[FighterState::BackwardBlock]={{-9,-8},{-20,-13}};
        offset[FighterState::CrouchBlock]={{-14,-65},{-19,-65}};

        offset[FighterState::Win]={{-85,51},{-74,84}};
        offset[FighterState::WinStart]={{-27,26}};

        offset[FighterState::TimeOverLoss]={{-18,-14}};
        offset[FighterState::DefeatedLoss]={{-196,-32},{-255,-66},{-297,-87}};

        offset[FighterState::JumpUP]={{-26,51},{-54,22},{-58,15},{-71,14},{-71,14},{-58,15},{-54,22},{-26,51}};
        offset[FighterState::JumpForward]={{-18,-5},{5,9},{55,45},{55,45},{5,9},{-18,-5}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
        offset[FighterState::JumpMP]=offset[FighterState::JumpLP]={{29,1},{1,3},{32,0},{-3,-4},{24,-4}};
        offset[FighterState::JumpHP]={{4,50},{36,19},{-15,15},{-72,-13}};
        offset[FighterState::JumpMK]=offset[FighterState::JumpLK]={{-20,12},{38,27},{65,7}};
        offset[FighterState::JumpHK]={{-12,-3},{-50,4},{-57,13},{-71,10},{-24,-6}};
        offset[FighterState::JumpAttackEnd]={{0,0}};
    }
    void Blanka::LoadAllBox() {

        boxes.pushbox.size[FighterState::Idle]={200,200};
        boxes.pushbox.offset[FighterState::Idle]={-38,9};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={200,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={-25,-27};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{180,80},{180,80},{180,80}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{180,125},{180,125},{180,125}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{40,80},{41,80},{35,83}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-20,37},{-20,36},{-20,41}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-44,-60},{-42,-60},{-41,-60}};
        boxes.hurtbox.head.offset[FighterState::Forward]={{90,50},{90,50},{90,50},{90,50},{90,50},{90,50},{90,50},{90,50}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{170,50}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{220,80}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{80,35}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{-19,-1}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{-30,-64}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{170,80},{170,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{220,80},{220,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{58,67},{66,18}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{0,25},{-19,-1}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-37,-62},{-41,-71}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{170,50},{170,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{220,80},{220,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{66,18},{58,67}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{-19,-1},{0,25}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{-30,-64},{-33,-57}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{150,100},{150,100}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{180,50},{180,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{79,10},{69,-1}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{-24,28},{-16,37}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{-22,-35},{-21,-34}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{33,69},{38,71}};
        boxes.hurtbox.leg.offset[FighterState::BackwardBlock]={{-24,-63},{-11,-63}};

        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{150,70},{150,70},{150,70},{150,70},{150,70},{150,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{300,70},{300,70},{300,70},{300,70},{300,70},{300,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{67,28},{112,9},{147,11},{153,6},{111,6},{65,31}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-12,13},{20,20},{50,18},{52,20},{12,21},{-25,28}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLP]={{-43,-48},{20,-45},{39,-48},{35,-52},{10,-48},{-46,-49}};

        boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]={{180,90},{180,100},{180,100}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]={{120,90},{200,90},{230,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]={{84,72},{71,59},{69,74}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-6,32},{18,32},{26,42}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{-18,-43},{23,-55},{51,-41}};

        boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMP]={{150,70},{150,70},{150,70},{150,70},{150,70},{150,70},{150,70},{150,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMP]={{100,70},{300,70},{300,70},{300,70},{300,70},{300,70},{300,70},{200,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMP]={{82,35},{281,25},{257,46},{275,71},{273,71},{258,48},{288,23},{82,32}};
        boxes.hurtbox.body.offset[FighterState::CrouchMP]={{-7,29},{206,10},{182,14},{194,14},{202,14},{179,11},{189,11},{-11,23}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMP]={{-23,-49},{130,-65},{126,-65},{141,-63},{141,-63},{112,-63},{142,-64},{-18,-59}};

        boxes.hurtbox.head.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchLK];
        boxes.hurtbox.body.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchLK];
        boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchLK];
        boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchLK];
        boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchLK];
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchLK];

        boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]={{140,70},{200,70},{200,70},{200,70},{200,70},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]={{180,80},{200,80},{200,80},{200,80},{200,80},{180,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]={{98,25},{105,32},{207,55},{207,55},{104,30},{87,27}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]={{9,25},{36,14},{134,36},{139,30},{36,12},{-12,25}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{-9,-36},{-24,-46},{41,-28},{43,-28},{-24,-45},{-24,-39}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]={{120,70},{140,70},{150,70},{150,70},{140,70},{120,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]={{180,90},{200,90},{200,90},{200,90},{200,90},{180,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]={{-59,69},{-18,55},{-23,34},{-24,33},{-31,54},{-42,67}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]={{31,18},{70,14},{77,17},{78,17},{56,19},{35,20}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{23,-59},{80,-66},{89,-64},{89,-64},{64,-59},{46,-64}};
        //hurtbox Stand Attack
        boxes.hurtbox.body.size[FighterState::LP]={{140,80},{180,80},{180,80},{180,80},{180,80},{140,80}};
        boxes.hurtbox.leg.size[FighterState::LP]={{240,125},{240,125},{240,125},{240,125},{240,125},{240,125}};
        boxes.hurtbox.head.offset[FighterState::LP]={{43,90},{55,104},{76,96},{76,96},{59,104},{49,95}};
        boxes.hurtbox.body.offset[FighterState::LP]={{-31,39},{-14,47},{-11,46},{-9,46},{-12,46},{-21,45}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-9,-60},{4,-61},{16,-65},{12,-68},{6,-69},{-6,-64}};

        boxes.hurtbox.body.size[FighterState::MP]={{140,80},{180,80},{180,80},{180,80}};
        boxes.hurtbox.leg.size[FighterState::MP]={{200,125},{220,125},{220,125},{220,125}};
        boxes.hurtbox.head.offset[FighterState::MP]={{54,61},{53,58},{53,48},{86,26}};
        boxes.hurtbox.body.offset[FighterState::MP]={{-9,8},{-2,3},{-9,-9},{5,-14}};
        boxes.hurtbox.leg.offset[FighterState::MP]={{-9,-122},{4,-125},{17,-123},{20,-121}};

        boxes.hurtbox.body.size[FighterState::HP]={{140,80},{140,80},{140,80},{140,80},{140,80},{140,80}};
        boxes.hurtbox.leg.size[FighterState::HP]={{200,125},{220,125},{220,125},{220,125},{220,125},{200,125}};
        boxes.hurtbox.head.offset[FighterState::HP]={{31,88},{36,96},{38,111},{38,111},{35,100},{30,88}};
        boxes.hurtbox.body.offset[FighterState::HP]={{-34,37},{-32,35},{-32,47},{-32,47},{-31,44},{-32,37}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{-24,-69},{-7,-66},{-2,-61},{-6,-61},{1,-62},{-12,-63}};

        boxes.hurtbox.head.offset[FighterState::LK]={{23,95},{12,93},{-1,80},{-1,80},{10,83},{17,92}};
        boxes.hurtbox.body.offset[FighterState::LK]={{-15,30},{-26,24},{-38,17},{-38,17},{-21,16},{-15,25}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{-11,-70},{-10,-74},{-19,-81},{-19,-81},{-15,-77},{-27,-80}};

        boxes.hurtbox.leg.size[FighterState::MK]={{160,125},{200,125},{160,125},{160,125},{200,125},{160,125}};
        boxes.hurtbox.head.offset[FighterState::MK]={{78,76},{53,77},{80,75},{83,73},{64,70},{82,70}};
        boxes.hurtbox.body.offset[FighterState::MK]={{7,42},{-4,37},{27,34},{28,34},{2,33},{13,36}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{37,-56},{10,-45},{41,-55},{41,-55},{14,-45},{22,-56}};

        boxes.hurtbox.body.size[FighterState::HK]={{120,80},{120,80},{120,80},{120,80},{120,80},{120,80},{120,80}};
        boxes.hurtbox.leg.size[FighterState::HK]={{120,125},{120,125},{120,125},{120,125},{120,125},{120,125},{120,125}};
        boxes.hurtbox.head.offset[FighterState::HK]={{-51,37},{-186,-11},{-89,8},{-71,25},{17,32},{93,33},{11,65}};
        boxes.hurtbox.body.offset[FighterState::HK]={{-63,38},{-63,38},{-63,38},{-63,38},{-63,38},{-63,38},{-63,38}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{-55,-59},{-55,-59},{-55,-59},{-55,-59},{-55,-59},{-55,-59},{-55,-59}};

        boxes.hurtbox.head.offset[FighterState::JumpUP]={{30,122},{8,57},{9,27},{11,9},{12,7},{9,26},{13,53},{30,118}};
        boxes.hurtbox.body.offset[FighterState::JumpUP]={{-10,74},{-40,21},{-45,11},{-48,0},{-48,0},{-45,11},{-40,21},{-10,74}};
        boxes.hurtbox.leg.size[FighterState::JumpUP]={{160,180},{190,125},{220,80},{200,90},{200,90},{220,80},{190,125},{160,180}};
        boxes.hurtbox.leg.offset[FighterState::JumpUP]={{-34,-65},{-49,-72},{-50,-70},{-43,-67},{-43,-67},{-50,-70},{-49,-72},{-34,-65}};

        boxes.hurtbox.body.size[FighterState::JumpForward]={{150,100},{150,100},{140,100},{140,100},{150,100},{150,100}};
        boxes.hurtbox.leg.size[FighterState::JumpForward]={{200,125},{190,110},{200,110},{200,110},{190,110},{200,125}};
        boxes.hurtbox.head.offset[FighterState::JumpForward]={{39,50},{55,68},{104,83},{105,80},{58,63},{40,54}};
        boxes.hurtbox.body.offset[FighterState::JumpForward]={{-3,31},{13,43},{69,63},{69,63},{13,43},{-3,31}};
        boxes.hurtbox.leg.offset[FighterState::JumpForward]={{-26,-41},{-13,-40},{18,-27},{18,-27},{-13,-40},{-26,-41}};

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

        boxes.hurtbox.body.size[FighterState::JumpMP]=boxes.hurtbox.body.size[FighterState::JumpLP]={{130,100},{130,100},{130,100},{130,100},{130,100}};
        boxes.hurtbox.leg.size[FighterState::JumpMP]=boxes.hurtbox.leg.size[FighterState::JumpLP]={{200,110},{200,110},{200,110},{200,110},{200,110}};
        boxes.hurtbox.head.offset[FighterState::JumpMP]=boxes.hurtbox.head.offset[FighterState::JumpLP]={{53,69},{69,67},{47,68},{69,67},{53,69}};
        boxes.hurtbox.body.offset[FighterState::JumpMP]=boxes.hurtbox.body.offset[FighterState::JumpLP]={{0,49},{-8,53},{-27,41},{-8,53},{0,49}};
        boxes.hurtbox.leg.offset[FighterState::JumpMP]=boxes.hurtbox.leg.offset[FighterState::JumpLP]={{-47,-42},{-56,-41},{-79,-49},{-56,-41},{-47,-42}};

        boxes.hurtbox.body.size[FighterState::JumpHP]={{150,100},{150,100},{170,100},{150,100}};
        boxes.hurtbox.leg.size[FighterState::JumpHP]={{180,125},{210,110},{210,140},{210,110}};
        boxes.hurtbox.head.offset[FighterState::JumpHP]={{36,13},{5,13},{6,10},{4,-12}};
        boxes.hurtbox.body.offset[FighterState::JumpHP]={{-31,10},{-68,2},{-88,21},{-91,2}};
        boxes.hurtbox.leg.offset[FighterState::JumpHP]={{-63,-90},{-93,-70},{-103,-59},{-109,-70}};

        boxes.hurtbox.body.size[FighterState::JumpMK]=boxes.hurtbox.body.size[FighterState::JumpLK]={{190,80},{190,100},{190,100}};
        boxes.hurtbox.leg.size[FighterState::JumpMK]=boxes.hurtbox.leg.size[FighterState::JumpLK]={{170,110},{190,115},{220,100}};
        boxes.hurtbox.head.offset[FighterState::JumpMK]=boxes.hurtbox.head.offset[FighterState::JumpLK]={{42,72},{101,97},{56,70}};
        boxes.hurtbox.body.offset[FighterState::JumpMK]=boxes.hurtbox.body.offset[FighterState::JumpLK]={{-15,44},{69,47},{30,8}};
        boxes.hurtbox.leg.offset[FighterState::JumpMK]=boxes.hurtbox.leg.offset[FighterState::JumpLK]={{-6,-20},{73,-31},{50,-62}};

        boxes.hurtbox.body.size[FighterState::JumpHK]={{110,125},{110,125},{110,125},{110,125},{110,125}};
        boxes.hurtbox.leg.size[FighterState::JumpHK]={{230,125},{230,125},{230,125},{230,125},{230,125}};
        boxes.hurtbox.head.offset[FighterState::JumpHK]={{4,61},{-38,46},{-103,48},{-62,51},{-7,56}};
        boxes.hurtbox.body.offset[FighterState::JumpHK]={{-32,25},{-55,12},{-94,3},{-77,15},{-38,21}};
        boxes.hurtbox.leg.offset[FighterState::JumpHK]={{0,-38},{45,-40},{58,-42},{19,-36},{-11,-51}};

        boxes.hurtbox.head.offset[FighterState::JumpAttackEnd]={{40,68}};
        boxes.hurtbox.body.offset[FighterState::JumpAttackEnd]={{-18,37}};
        boxes.hurtbox.leg.offset[FighterState::JumpAttackEnd]={{-18,-46}};
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={160,40};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{216,4},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMP]={150,70};
        boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{310,75},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]={200,100};
        boxes.hitbox.offset[FighterState::CrouchHP]={{-1,-1},{-1,-1},{265,105},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchLK]={212,45};
        boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{-1,-1},{230,-35}};
        boxes.hitbox.size[FighterState::CrouchMK]=boxes.hitbox.size[FighterState::CrouchLK];
        boxes.hitbox.offset[FighterState::CrouchMK]=boxes.hitbox.offset[FighterState::CrouchLK];
        boxes.hitbox.size[FighterState::CrouchHK]={220,70};
        boxes.hitbox.offset[FighterState::CrouchHK]={{-1,-1},{-1,-1},{268,-80},{-1,-1},{-1,-1},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={180,50};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{168,61},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={160,47};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{171,-21},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={160,80};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{142,60},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={180,80};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{185,18},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MK]={160,60};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{185,93},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={180,140};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{134,36},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

        //hitbox Jump Attack
        boxes.hitbox.size[FighterState::JumpMP]=boxes.hitbox.size[FighterState::JumpLP]={170,50};
        boxes.hitbox.offset[FighterState::JumpMP]=boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{-1,-1},{90,-10},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::JumpHP]={195,60};
        boxes.hitbox.offset[FighterState::JumpHP]={{-1,-1},{120,11},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::JumpMK]=boxes.hitbox.size[FighterState::JumpLK]={220,70};
        boxes.hitbox.offset[FighterState::JumpMK]=boxes.hitbox.offset[FighterState::JumpLK]={{-1,-1},{-1,-1},{160,-84}};
        boxes.hitbox.size[FighterState::JumpHK]={250,80};
        boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{-1,-1},{80,-54},{-1,-1},{-1,-1}};
    }
    void Blanka::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(4, "Special_1");
        offset[FighterState::Special_1]={{-23,-33},{-14,-37},{-8,-19},{-15,-51}};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LP]={90,30,360,30};

        boxes.hurtbox.body.size[FighterState::Special_1]={{150,80},{150,80},{180,80},{180,80}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{180,100},{180,100},{180,100},{180,100}};
        boxes.hurtbox.head.offset[FighterState::Special_1]={{84,39},{84,39},{90,12},{89,14}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{3,28},{9,26},{4,7},{4,7}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{-4,-49},{-4,-49},{-5,-59},{-5,-59}};
        boxes.hitbox.size[FighterState::Special_1]={360,250};
        boxes.hitbox.offset[FighterState::Special_1]={{-1,-1},{-1,-1},{17,-7},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::LP]=20;
        SpecialMoveData.attackdata[FighterState::Special_1].HitStrength[Keys::LP]=HitStrength::SP;

        StateEnter[FighterState::Special_1]=[this] { ElectricThunderStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { ElectricThunderStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Blanka/SP1.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={};
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ALL_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Null;

        animations[FighterState::Special_2]=ActionInit(8, "Special_2");
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LP]={45,45,45,45,45,45,45,45};

        boxes.hurtbox.body.size[FighterState::Special_2]={{180,80},{180,80},{180,80},{180,80},{180,80},{180,80},{180,80},{180,80}};
        boxes.hurtbox.leg.size[FighterState::Special_2]={{180,125},{180,125},{180,125},{180,125},{180,125},{180,125},{180,125},{180,125}};
        boxes.hurtbox.head.offset[FighterState::Special_2]={{-52,-60},{-84,-20},{-80,19},{-31,60},{58,51},{90,13},{60,-19},{13,-62}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{19,-24},{-2,-28},{-28,-7},{-26,6},{-11,14},{9,20},{-2,19},{0,2}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{-7,45},{24,40},{54,5},{44,-15},{0,-38},{-26,-28},{-74,2},{-64,20}};

        boxes.hitbox.size[FighterState::Special_2]={220,200};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{-1,-1},{2,2},{9,2},{14,6},{11,9},{15,0}};

        StateEnter[FighterState::Special_2]=[this] { RollingAttackStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { RollingAttackStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Blanka/SP2.wav");

        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::LP]={20,0};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::MP]={25,0};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::HP]={30,0};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LP]=10;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::MP]=15;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::HP]=20;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LP]=HitStrength::H;

        SpecialMoveData.SkillCommand[FighterState::Special_2].command={
            SpecialMoveDirection::Forward,
            SpecialMoveDirection::Backward
        };
        SpecialMoveData.SkillCommand[FighterState::Special_2].requiredAttack=AttackButton::ANY_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_2].commandtype=CommandType::Pressed;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::LP]=500;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::MP]=750;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::HP]=1000;
        SpecificStates.borderCheckStates.insert(FighterState::Special_2);

        animations[FighterState::SpecialRecovery_2]=ActionInit(7, "SpecialRecovery_2");

        offset[FighterState::SpecialRecovery_2]={{-34,14},{-33,15},{-30,17},{-14,16},{-30,15},{50,-12},{61,-2}};
        frames[FighterState::SpecialRecovery_2]={90,90,90,90,120,120,120,150};

        boxes.hurtbox.body.size[FighterState::SpecialRecovery_2]={{180,80},{180,80},{150,120},{180,90},{180,80},{100,250},{100,180}};
        boxes.hurtbox.leg.size[FighterState::SpecialRecovery_2]={{180,125},{180,125},{180,125},{180,125},{240,100},{180,100}};
        boxes.hurtbox.head.offset[FighterState::SpecialRecovery_2]={{37,-41},{85,2},{91,78},{-47,104},{-115,-60},{6,-24},{65,-53}};
        boxes.hurtbox.body.offset[FighterState::SpecialRecovery_2]={{33,29},{-2,34},{19,26},{-15,23},{-78,3},{-13,-24},{68,-47}};
        boxes.hurtbox.leg.offset[FighterState::SpecialRecovery_2]={{-53,-23},{-45,-48},{-20,-69},{57,-34},{87,32},{122,90},{172,73}};

        StateEnter[FighterState::SpecialRecovery_2]=[this] { RollingAttackRecoveryStateEnter(); };
        StateUpdate[FighterState::SpecialRecovery_2]=[this] { RollingAttackRecoveryStateUpdate(); };

        Initialvelocity.x[FighterState::SpecialRecovery_2]=-10;
        Initialvelocity.y[FighterState::SpecialRecovery_2]=38;
        SpecificStates.borderCheckStates.insert(FighterState::SpecialRecovery_2);

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Blanka/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Blanka/Loss.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].SpecialNumer=SpecialNumer::Special_1;
        SpecialMoveData.SkillCommand[FighterState::Special_2].SpecialNumer=SpecialNumer::Special_2;

        SpecificStates.SpecialStates.insert(FighterState::Special_1);
        SpecificStates.SpecialStates.insert(FighterState::Special_2);

        SpecificStates.SpecialAttackStates.insert(FighterState::Special_1);
        SpecificStates.SpecialAttackStates.insert(FighterState::Special_2);
    }
    void Blanka::ElectricThunderStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::punch);
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Blanka::ElectricThunderStateUpdate() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Blanka::RollingAttackStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::punch);
        LoadCurrentSpecialMove(ButtonType);
        velocity=GetInitialvelocity();
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Blanka::RollingAttackStateUpdate() {
        if(ActionNow->GetCurrentFrameIndex()>=8){ResetVelocity();}
        if(HitEnemy) {
            ChangeState(FighterState::SpecialRecovery_2);
        }
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Blanka::RollingAttackRecoveryStateEnter() {
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Blanka::RollingAttackRecoveryStateUpdate() {
        if(GetCharacterIsOnFloor()&&velocity.y<0){velocity.y=0;}
        else{velocity.y+=Gravity*Time::GetDeltaTimeMs()/1000;}
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }
}
