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
        animations[FighterState::MK] =animations[FighterState::LK] = ActionInit(5, "LK");
        animations[FighterState::HK] = ActionInit(3, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(4, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(3, "GetUp");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(1, "CrouchBlock");

        animations[FighterState::CrouchHP] = animations[FighterState::CrouchMP] =animations[FighterState::CrouchLP] = ActionInit(7, "CrouchLP");
        animations[FighterState::CrouchHK] = animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");

        animations[FighterState::JumpHP] =animations[FighterState::JumpMP] =animations[FighterState::JumpLP] = ActionInit(3, "JumpLP");
        animations[FighterState::JumpLK] = ActionInit(2, "JumpLK");
        animations[FighterState::JumpMK] = ActionInit(3, "JumpMK");
        animations[FighterState::JumpHK] = ActionInit(3, "JumpHK");
        animations[FighterState::JumpAttackEnd] = ActionInit(1, "JumpAttackEnd");

        animations[FighterState::WinStart]=ActionInit(4, "WinStart");
        animations[FighterState::Win]=ActionInit(1, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(2, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(5, "DefeatedLoss");

        frames[FighterState::Idle]={150, 180, 180, 150};
        frames[FighterState::Forward]=frames[FighterState::Backward]={120, 150, 150, 120};
        frames[FighterState::JumpUP]=frames[FighterState::JumpForward]={90,120,150,120,90};
        std::vector<int> reversedframe = frames[FighterState::JumpForward];
        std::reverse(reversedframe.begin(), reversedframe.end());
        frames[FighterState::JumpBackward] = reversedframe;
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60};
        frames[FighterState::CrouchUp]={60,60};
        frames[FighterState::LP]={60,90,30,30,30,30,30};
        frames[FighterState::MP]={30,30,60,120,60,30,30};
        frames[FighterState::HP]={30,60,60,180,90,60,60};
        frames[FighterState::LK]={60,90,120,90,60};
        frames[FighterState::MK]={90,120,180,120,90};
        frames[FighterState::HK]={120,180,240};

        frames[FighterState::CrouchLP]={30,30,60,90,60,30,30};
        frames[FighterState::CrouchMP]={30,60,60,120,90,60,30};
        frames[FighterState::CrouchHP]={30,60,90,180,120,60,60};
        frames[FighterState::CrouchLK]={60,90,60};
        frames[FighterState::CrouchMK]={90,120,90};
        frames[FighterState::CrouchHK]={120,180,120};

        frames[FighterState::JumpLP]={60,240,60};
        frames[FighterState::JumpMP]={90,360,90};
        frames[FighterState::JumpHP]={120,480,120};
        frames[FighterState::JumpLK]={60,240};
        frames[FighterState::JumpMK]={60,60,360};
        frames[FighterState::JumpHK]={120,480,90};
        frames[FighterState::JumpAttackEnd]={100};

        frames[FighterState::HurtHeadL] = {90,90};
        frames[FighterState::HurtHeadM] = {160,160};
        frames[FighterState::HurtHeadH] = {210,210};
        frames[FighterState::HurtBodyL] = {90,90};
        frames[FighterState::HurtBodyM] = {160,160};
        frames[FighterState::HurtBodyH] = {210,210};

        frames[FighterState::KnockDownL] = {75,120,120,75};
        frames[FighterState::KnockDownM] = {105,120,120,105};
        frames[FighterState::KnockDownH] = {130,160,160,130};
        frames[FighterState::GetUp] = {150,150,150};

        frames[FighterState::BackwardBlock] = {60,60};
        frames[FighterState::CrouchBlock] = {120};

        frames[FighterState::WinStart]={200, 200, 200, 200};
        frames[FighterState::Win]={200};

        frames[FighterState::TimeOverLoss]={180, 180};
        frames[FighterState::DefeatedLoss]={180,180,180,180,180};
    }
    void Vega::LoadOffsetVelocity() {
        StateEnter[FighterState::HK] = [this] { HKStateEnter(); };
        StateUpdate[FighterState::HK] = [this] {HKStateUpdate(); };
        Initialvelocity.x[FighterState::HK]=6;
        attacktype[FighterState::HK]=AttackType::Lower;
        attacktype[FighterState::CrouchLK]=attacktype[FighterState::CrouchMK]=attacktype[FighterState::CrouchHK]=AttackType::Lower;
        offset[FighterState::Idle]={{0,0},{0,-2},{-3,-7},{-1,-4}};
        offset[FighterState::Crouch]={{-1,-52}};
        offset[FighterState::CrouchDown]={{-1,-10},{1,-38}};
        offset[FighterState::CrouchUp]={{1,-38},{-1,-10}};
        //Stand attack offset
        offset[FighterState::LP]={{-4,-14},{25,-5},{26,-3},{26,-3},{26,-5},{-5,-15},{-7,-12}};
        offset[FighterState::HP]=offset[FighterState::MP]={{-32,-11},{-49,-20},{-50,-17},{-9,-25},{-8,-26},{-8,-23},{-8,-26},{-32,-9},{-33,-10}};
        offset[FighterState::MK]=offset[FighterState::LK]={{13,5},{84,14},{239,13},{84,14},{13,5}};
        //Crouch attack offset
        offset[FighterState::CrouchHP]=offset[FighterState::CrouchMP]=offset[FighterState::CrouchLP]={{-4,-39},{-1,-37},{-2,-38},{35,-44},{33,-44},{-5,-40},{-5,-39}};
        offset[FighterState::CrouchHK]=offset[FighterState::CrouchMK]=offset[FighterState::CrouchLK]={{-11,-43},{3,-44},{-8,-43}};
        offset[FighterState::HK] ={{-22,-2},{-13,-14},{-9,-42}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-12,-4},{-30,-6}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{-9,-4},{-54,-6}};

        offset[FighterState::KnockDownL]=offset[FighterState::KnockDownM]=offset[FighterState::KnockDownH]={{-8,-4},{-56,-25},{-64,-36},{-121,-98}};
        offset[FighterState::GetUp]={{52,-76},{61,-59},{48,-50}};

        offset[FighterState::BackwardBlock]={{-22,0},{-53,-12}};
        offset[FighterState::CrouchBlock]={{-16,-45}};

        offset[FighterState::Win]={{11,5}};
        offset[FighterState::WinStart]={{17,3},{11,3},{13,6},{8,5}};

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

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{160,75},{160,125}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{4,47},{5,104}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{-44,-2},{-33,48}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{-6,-81},{-18,-56}};

        /*std::vector<glm::vec2> reversedhurtbox = boxes.hurtbox.head.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.head.offset[FighterState::CrouchUp]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.body.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.body.offset[FighterState::CrouchUp]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.leg.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]=reversedhurtbox;*/

        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{130,60}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{160,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{-15,71}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{-28,25}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{-1,-49}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{-30,113},{-48,93}};
        boxes.hurtbox.body.offset[FighterState::BackwardBlock]={{-57,45},{-103,36}};
        boxes.hurtbox.leg.offset[FighterState::BackwardBlock]={{-28,-71},{-54,-76}};

        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchHP]=boxes.hurtbox.head.size[FighterState::CrouchMP]=boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]=boxes.hurtbox.body.size[FighterState::CrouchMP]=boxes.hurtbox.body.size[FighterState::CrouchLP]={{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]=boxes.hurtbox.leg.size[FighterState::CrouchMP]=boxes.hurtbox.leg.size[FighterState::CrouchLP]={{160,90},{160,90},{160,90},{160,90},{160,90},{160,90},{160,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]=boxes.hurtbox.head.offset[FighterState::CrouchMP]=boxes.hurtbox.head.offset[FighterState::CrouchLP]={{-37,76},{39,80},{37,78},{63,69},{62,69},{-37,75},{-35,80}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]=boxes.hurtbox.body.offset[FighterState::CrouchMP]=boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-45,33},{4,32},{4,32},{8,37},{14,36},{-43,32},{-43,32}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]=boxes.hurtbox.leg.offset[FighterState::CrouchMP]=boxes.hurtbox.leg.offset[FighterState::CrouchLP]={{2,-43},{26,-47},{25,-47},{22,-47},{25,-47},{10,-51},{10,-51}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]=boxes.hurtbox.head.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]=boxes.hurtbox.body.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchLK]={{120,70},{110,70},{120,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]=boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchLK]={{170,90},{190,80},{170,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]=boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchLK]={{-7,70},{-82,67},{-7,70}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]=boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-6,36},{-65,20},{-6,36}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]=boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{13,-50},{-22,-52},{13,-50}};

         //hurtbox Stand Attack
        boxes.hurtbox.head.offset[FighterState::LP]={{1,105},{20,120},{20,120},{20,120},{20,120},{3,99},{2,103}};
        boxes.hurtbox.body.offset[FighterState::LP]={{-29,63},{-10,73},{-10,73},{-10,73},{-10,73},{-32,54},{-32,54}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-32,-56},{-23,-55},{-23,-56},{-23,-56},{-23,-56},{-24,-63},{-23,-60}};

        boxes.hurtbox.head.offset[FighterState::HP]=boxes.hurtbox.head.offset[FighterState::MP]={{16,108},{16,89},{17,92},{35,81},{39,81},{39,81},{39,81},{18,107},{17,107}};
        boxes.hurtbox.body.offset[FighterState::HP]=boxes.hurtbox.body.offset[FighterState::MP]={{-20,55},{-26,44},{-28,49},{-20,51},{-15,48},{-11,50},{-8,51},{-13,60},{-10,60}};
        boxes.hurtbox.leg.size[FighterState::HP]=boxes.hurtbox.leg.size[FighterState::MP]={{160,130},{150,110},{150,110},{140,100},{140,100},{140,100},{140,100},{170,120},{170,120}};
        boxes.hurtbox.leg.offset[FighterState::HP]=boxes.hurtbox.leg.offset[FighterState::MP]={{2,-58},{-11,-64},{-11,-64},{-14,-57},{-20,-56},{-18,-54},{-19,-53},{-4,-58},{-3,-60}};

        boxes.hurtbox.head.offset[FighterState::MK]=boxes.hurtbox.head.offset[FighterState::LK]={{5,117},{35,132},{119,133},{34,133},{7,117}};
        boxes.hurtbox.body.offset[FighterState::MK]=boxes.hurtbox.body.offset[FighterState::LK]={{5,51},{26,87},{87,76},{26,87},{5,51}};
        boxes.hurtbox.leg.size[FighterState::MK]=boxes.hurtbox.leg.size[FighterState::LK]={{160,140},{120,160},{80,160},{120,160},{160,140}};
        boxes.hurtbox.leg.offset[FighterState::MK]=boxes.hurtbox.leg.offset[FighterState::LK]={{22,-72},{62,-49},{142,-29},{62,-49},{22,-72}};

        boxes.hurtbox.head.size[FighterState::HK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::HK]={{120,70},{110,80},{120,70}};
        boxes.hurtbox.leg.size[FighterState::HK]={{100,160},{140,120},{170,90}};
        boxes.hurtbox.head.offset[FighterState::HK]={{-45,110},{-71,80},{6,27}};
        boxes.hurtbox.body.offset[FighterState::HK]={{-28,66},{-68,27},{7,-12}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{-63,-62},{-7,-70},{14,-91}};

        //hurtbox Jump
        boxes.hurtbox.body.size[FighterState::JumpForward]=boxes.hurtbox.body.size[FighterState::JumpUP]={{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::JumpForward]=boxes.hurtbox.leg.size[FighterState::JumpUP]={{100,150},{120,125},{140,125},{140,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::JumpForward]=boxes.hurtbox.head.offset[FighterState::JumpUP]={{26,115},{20,103},{-7,83},{17,107},{25,121}};
        boxes.hurtbox.body.offset[FighterState::JumpForward]=boxes.hurtbox.body.offset[FighterState::JumpUP]={{2,56},{-7,48},{-42,39},{-8,47},{3,58}};
        boxes.hurtbox.leg.offset[FighterState::JumpForward]=boxes.hurtbox.leg.offset[FighterState::JumpUP]={{-3,-35},{-4,-36},{-24,-22},{-2,-33},{-1,-47}};

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

        boxes.hurtbox.body.size[FighterState::JumpHP]=boxes.hurtbox.body.size[FighterState::JumpMP]=boxes.hurtbox.body.size[FighterState::JumpLP]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::JumpHP]=boxes.hurtbox.leg.size[FighterState::JumpMP]=boxes.hurtbox.leg.size[FighterState::JumpLP]={{140,100},{140,130},{140,100}};
        boxes.hurtbox.head.offset[FighterState::JumpHP]=boxes.hurtbox.head.offset[FighterState::JumpMP]=boxes.hurtbox.head.offset[FighterState::JumpLP]={{125,-35},{65,76},{123,-37}};
        boxes.hurtbox.body.offset[FighterState::JumpHP]=boxes.hurtbox.body.offset[FighterState::JumpMP]=boxes.hurtbox.body.offset[FighterState::JumpLP]={{51,-55},{26,35},{51,-55}};
        boxes.hurtbox.leg.offset[FighterState::JumpHP]=boxes.hurtbox.leg.offset[FighterState::JumpMP]=boxes.hurtbox.leg.offset[FighterState::JumpLP]={{-65,-47},{-89,-37},{-65,-47}};

        boxes.hurtbox.body.size[FighterState::JumpLK]={{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::JumpLK]={{130,140},{250,100}};
        boxes.hurtbox.head.offset[FighterState::JumpLK]={{-20,107},{-64,28}};
        boxes.hurtbox.body.offset[FighterState::JumpLK]={{19,64},{-49,-18}};
        boxes.hurtbox.leg.offset[FighterState::JumpLK]={{26,-32},{6,-92}};

        boxes.hurtbox.body.size[FighterState::JumpMK]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::JumpMK]={{120,140},{130,140},{250,100}};
        boxes.hurtbox.head.offset[FighterState::JumpMK]={{12,127},{80,107},{36,28}};
        boxes.hurtbox.body.offset[FighterState::JumpMK]={{57,95},{119,64},{51,-18}};
        boxes.hurtbox.leg.offset[FighterState::JumpMK]={{50,-21},{126,-32},{94,-92}};

        boxes.hurtbox.body.size[FighterState::JumpHK]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::JumpHK]={{150,110},{250,100},{150,110}};
        boxes.hurtbox.head.offset[FighterState::JumpHK]={{-18,84},{5,36},{-16,83}};
        boxes.hurtbox.body.offset[FighterState::JumpHK]={{-6,43},{-16,3},{-6,43}};
        boxes.hurtbox.leg.offset[FighterState::JumpHK]={{25,-32},{12,-52},{25,-32}};


        boxes.hurtbox.head.offset[FighterState::JumpAttackEnd]={{26,113}};
        boxes.hurtbox.body.offset[FighterState::JumpAttackEnd]={{8,71}};
        boxes.hurtbox.leg.size[FighterState::JumpAttackEnd]={{110,170}};
        boxes.hurtbox.leg.offset[FighterState::JumpAttackEnd]={{-7,-44}};

        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchHP]=boxes.hitbox.size[FighterState::CrouchMP]=boxes.hitbox.size[FighterState::CrouchLP]={180,50};
        boxes.hitbox.offset[FighterState::CrouchHP]=boxes.hitbox.offset[FighterState::CrouchMP]=boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{-1,-1},{-1,-1},{143,44},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHK]=boxes.hitbox.size[FighterState::CrouchMK]=boxes.hitbox.size[FighterState::CrouchLK]={265,60};
        boxes.hitbox.offset[FighterState::CrouchHK]=boxes.hitbox.offset[FighterState::CrouchMK]=boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{83,-46},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={175,60};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{125,110},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]=boxes.hitbox.size[FighterState::MP]={140,70};
        boxes.hitbox.offset[FighterState::HP]=boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{-1,-1},{110,34},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MK]=boxes.hitbox.size[FighterState::LK]={280,60};
        boxes.hitbox.offset[FighterState::MK]=boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{260,56},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={250,100};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{61,-66},{-1,-1}};
        //hitbox Jump Attack
        boxes.hitbox.size[FighterState::JumpHP]=boxes.hitbox.size[FighterState::JumpMP]=boxes.hitbox.size[FighterState::JumpLP]={220,50};
        boxes.hitbox.offset[FighterState::JumpHP]=boxes.hitbox.offset[FighterState::JumpMP]=boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{110,44},{-1,-1}};
        boxes.hitbox.size[FighterState::JumpLK]={240,70};
        boxes.hitbox.offset[FighterState::JumpLK]={{-1,-1},{100,-84}};
        boxes.hitbox.size[FighterState::JumpMK]={240,70};
        boxes.hitbox.offset[FighterState::JumpMK]={{-1,-1},{-1,-1},{200,-84}};
        boxes.hitbox.size[FighterState::JumpHK]={260,70};
        boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{140,-60},{-1,-1}};
    }
    void Vega::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(9, "Special_1");
        offset[FighterState::Special_1]={{-31,-22},{23,-4},{-12,51},{-23,49},{-60,-4},{-29,-21},{-2,-56},{-1,-38},{-3,-11}};
        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::LK]={9,0};
        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::MK]={11,0};
        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::HK]={13,0};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LK]={30,60,90,120,120,90,90,90,60};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::MK]={30,60,90,150,150,120,90,90,60};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::HK]={30,60,90,180,180,150,90,90,60};

        boxes.hurtbox.body.size[FighterState::Special_1]={{100,100},{150,80},{100,140},{140,80},{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Special_1]={{160,125},{120,150},{50,140},{150,130},{160,100},{160,125},{160,80},{160,100},{160,125}};
        boxes.hurtbox.head.offset[FighterState::Special_1]={{58,92},{187,60},{52,-63},{-132,61},{-86,125},{59,97},{37,29},{33,60},{34,117}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{-9,43},{96,94},{110,10},{-59,13},{-78,60},{2,47},{-23,-24},{-18,5},{-3,57}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{18,-49},{-46,21},{90,140},{10,56},{-19,-3},{18,-56},{27,-89},{22,-66},{11,-55}};

        boxes.hitbox.size[FighterState::Special_1]={200,120};
        boxes.hitbox.offset[FighterState::Special_1]={{-1,-1},{-1,-1},{-1,-1},{118,38},{36,-33},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::LK]=8;
        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::MK]=12;
        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::HK]=15;

        SpecialMoveData.attackdata[FighterState::Special_1].HitStrength[Keys::LK]=HitStrength::H;

        StateEnter[FighterState::Special_1]=[this] { DoubleKneePressStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { DoubleKneePressStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP1.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={
            SpecialMoveDirection::Forward,
            SpecialMoveDirection::Forward_down,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ANY_KICK;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Command;
        SpecificStates.borderCheckStates.insert(FighterState::Special_1);

        animations[FighterState::Special_2]=ActionInit(10, "Special_2");
        offset[FighterState::Special_2]={{-17,0},{-52,-5},{-27,-12},{66,2},{93,20},{93,20},{88,19},{90,20},{70,4},{-3,-7}};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::LP]={16,0};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::MP]={20,0};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::HP]={24,0};

        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LP]={30,60,60,60,90,90,90,90,120,90};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::MP]={30,60,60,60,120,120,120,120,120,90};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::HP]={30,60,60,60,150,150,150,150,120,90};

        boxes.hurtbox.body.size[FighterState::Special_2]={{100,100},{140,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Special_2]={{160,125},{140,125},{160,125},{160,125},{200,80},{200,80},{200,80},{200,80},{160,125},{160,125}};
        boxes.hurtbox.head.offset[FighterState::Special_2]={{-27,114},{-43,99},{49,83},{164,81},{221,49},{259,13},{215,-10},{258,15},{168,82},{18,100}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{-53,52},{-81,41},{-19,47},{113,23},{151,6},{192,12},{151,36},{168,16},{109,24},{-17,46}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{-17,-70},{-36,-67},{8,-69},{18,-36},{16,-6},{24,14},{19,41},{29,19},{31,-30},{2,-69}};

        boxes.hitbox.size[FighterState::Special_2]={480,200};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{110,2},{115,14},{112,36},{102,18},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LP]=10;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::MP]=15;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::HP]=20;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LP]=HitStrength::SP;

        StateEnter[FighterState::Special_2]=[this] { PsychoCrusherStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { PsychoCrusherStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP2_L.wav");
        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::MP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP2_L.wav");
        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::HP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP2_H.wav");

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
        SpecificStates.InvincibleForFlyObj.insert(FighterState::Special_2);
        SpecificStates.CrossState.insert(FighterState::Special_2);

        animations[FighterState::Special_3]=ActionInit(5, "Special_3");
        offset[FighterState::Special_3]={{-1,-21},{28,34},{2,29},{5,27},{1,23}};
        SpecialMoveData.animationData[FighterState::Special_3].initialvelocitys[Keys::LK]={9,38};
        SpecialMoveData.animationData[FighterState::Special_3].initialvelocitys[Keys::MK]={17,38};
        SpecialMoveData.animationData[FighterState::Special_3].initialvelocitys[Keys::HK]={25,38};

        SpecialMoveData.animationData[FighterState::Special_3].frames[Keys::LK]={90,120,180,120,120};
        SpecialMoveData.animationData[FighterState::Special_3].frames[Keys::MK]={90,120,180,120,120};
        SpecialMoveData.animationData[FighterState::Special_3].frames[Keys::HK]={90,120,180,120,120};

        boxes.hurtbox.body.size[FighterState::Special_3]={{140,100},{120,100},{120,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Special_3]={{160,125},{130,125},{160,125},{160,125},{160,125}};
        boxes.hurtbox.head.offset[FighterState::Special_3]={{59,96},{55,171},{41,153},{36,112},{34,146}};
        boxes.hurtbox.body.offset[FighterState::Special_3]={{-6,47},{35,113},{10,97},{-1,69},{9,85}};
        boxes.hurtbox.leg.offset[FighterState::Special_3]={{21,-52},{22,12},{21,12},{19,17},{20,4}};

        StateEnter[FighterState::Special_3]=[this] { HeadStompStateEnter(); };
        StateUpdate[FighterState::Special_3]=[this] { HeadStompStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_3].sound[Keys::LK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP3.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_3].command={
            SpecialMoveDirection::Up,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_3].requiredAttack=AttackButton::ANY_KICK;
        SpecialMoveData.SkillCommand[FighterState::Special_3].commandtype=CommandType::Pressed;
        SpecialMoveData.SkillCommand[FighterState::Special_3].chargetime[Keys::LK]=500;
        SpecialMoveData.SkillCommand[FighterState::Special_3].chargetime[Keys::MK]=750;
        SpecialMoveData.SkillCommand[FighterState::Special_3].chargetime[Keys::HK]=1000;
        SpecificStates.borderCheckStates.insert(FighterState::Special_3);

        animations[FighterState::Special_4]=ActionInit(2, "Special_4");

        offset[FighterState::Special_4]={{-37,-9},{-9,29}};
        frames[FighterState::Special_4]={90,240};

        attacktype[FighterState::Special_4]=AttackType::Upper;
        hitstrength[FighterState::Special_4]=HitStrength::H;
        attacks[FighterState::Special_4]=15;

        boxes.hurtbox.body.size[FighterState::Special_4]={{120,100},{120,100}};
        boxes.hurtbox.leg.size[FighterState::Special_4]={{120,130},{80,140}};
        boxes.hurtbox.head.offset[FighterState::Special_4]={{30,107},{22,172}};
        boxes.hurtbox.body.offset[FighterState::Special_4]={{-13,39},{29,88}};
        boxes.hurtbox.leg.offset[FighterState::Special_4]={{0,-38},{25,-15}};

        boxes.hitbox.size[FighterState::Special_4]={150,200};
        boxes.hitbox.offset[FighterState::Special_4]={{-1,-1},{25,-36}};

        StateEnter[FighterState::Special_4]=[this] { HeadStompAttackStateEnter(); };
        StateUpdate[FighterState::Special_4]=[this] { HeadStompAttackStateUpdate(); };

        SpecificStates.borderCheckStates.insert(FighterState::Special_4);
        soundeffect[FighterState::Special_4]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP4.wav");

        animations[FighterState::SpecialRecovery_4]=ActionInit(6, "SpecialRecovery_4");

        offset[FighterState::SpecialRecovery_4]={{-11,-2},{-75,32},{-11,22},{-1,45},{-55,18},{5,-2}};
        frames[FighterState::SpecialRecovery_4]={120,150,150,150,120,120};

        boxes.hurtbox.body.size[FighterState::SpecialRecovery_4]={{140,100},{100,100},{120,80},{100,100},{100,100},{140,100}};
        boxes.hurtbox.leg.size[FighterState::SpecialRecovery_4]={{140,125},{140,125},{160,110},{120,125},{120,125},{140,125}};
        boxes.hurtbox.head.offset[FighterState::SpecialRecovery_4]={{27,108},{-88,143},{-153,2},{50,-64},{100,41},{41,116}};
        boxes.hurtbox.body.offset[FighterState::SpecialRecovery_4]={{-5,46},{-118,70},{-58,55},{-45,8},{-12,-18},{15,55}};
        boxes.hurtbox.leg.offset[FighterState::SpecialRecovery_4]={{-13,-45},{-75,-20},{71,37},{-42,87},{-107,6},{11,-39}};

        StateEnter[FighterState::SpecialRecovery_4]=[this] { HeadStompRecoveryStateEnter(); };
        StateUpdate[FighterState::SpecialRecovery_4]=[this] { HeadStompRecoveryStateUpdate(); };

        Initialvelocity.x[FighterState::SpecialRecovery_4]=-10;
        Initialvelocity.y[FighterState::SpecialRecovery_4]=38;
        SpecificStates.borderCheckStates.insert(FighterState::SpecialRecovery_4);


        animations[FighterState::SpecialDerive_4]=ActionInit(2, "SpecialDerive_4");

        offset[FighterState::SpecialDerive_4]={{62,23},{82,8}};
        frames[FighterState::SpecialDerive_4]={90,160};

        attacktype[FighterState::SpecialDerive_4]=AttackType::Upper;
        hitstrength[FighterState::SpecialDerive_4]=HitStrength::H;
        attacks[FighterState::SpecialDerive_4]=15;

        boxes.hurtbox.body.size[FighterState::SpecialDerive_4]={{140,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::SpecialDerive_4]={{140,125},{160,125}};
        boxes.hurtbox.head.offset[FighterState::SpecialDerive_4]={{129,-33},{91,59}};
        boxes.hurtbox.body.offset[FighterState::SpecialDerive_4]={{10,-64},{34,3}};
        boxes.hurtbox.leg.offset[FighterState::SpecialDerive_4]={{-79,-46},{-58,-55}};

        boxes.hitbox.size[FighterState::SpecialDerive_4]={150,100};
        boxes.hitbox.offset[FighterState::SpecialDerive_4]={{-1,-1},{168,28}};

        StateEnter[FighterState::SpecialDerive_4]=[this] { HeadStompDeriveStateEnter(); };
        StateUpdate[FighterState::SpecialDerive_4]=[this] { HeadStompDeriveStateUpdate(); };

        SpecificStates.borderCheckStates.insert(FighterState::SpecialDerive_4);
        soundeffect[FighterState::SpecialDerive_4]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/SP_4_Derive.wav");

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Vega/Loss.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].SpecialNumer=SpecialNumer::Special_1;
        SpecialMoveData.SkillCommand[FighterState::Special_2].SpecialNumer=SpecialNumer::Special_2;
        SpecialMoveData.SkillCommand[FighterState::Special_3].SpecialNumer=SpecialNumer::Special_3;

        SpecificStates.SpecialStates.insert(FighterState::Special_1);
        SpecificStates.SpecialStates.insert(FighterState::Special_2);
        SpecificStates.SpecialStates.insert(FighterState::Special_3);

        SpecificStates.SpecialAttackStates.insert(FighterState::Special_1);
        SpecificStates.SpecialAttackStates.insert(FighterState::Special_2);
        SpecificStates.SpecialAttackStates.insert(FighterState::Special_4);
        SpecificStates.SpecialAttackStates.insert(FighterState::SpecialDerive_4);
    }
    void Vega::HKStateEnter() {
        controller->ClearAiAttack();
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        PlayCurrentSound();
    }
    void Vega::HKStateUpdate() {
        if(ActionNow->GetCurrentFrameIndex()==1) {velocity=GetInitialvelocity();}
        else if(velocity.x > 0) {ResetVelocity();}
        if(enemy->GetCharacterIsInBorder()&&HitEnemy
    &&(enemy->GetSpecificState().HurtStates.count(enemy->GetCurrentState())||
        enemy->GetSpecificState().BlockStates.count(enemy->GetCurrentState())))
        {velocity.x=enemy->GetVelocity().x;}
        if (GetAnimationIsEnd()&&SpecificStates.CrouchAttackStates.count(currentState)) {ChangeState(FighterState::Crouch);}
        else if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Vega::DoubleKneePressStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Vega::DoubleKneePressStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex() ==1) {
            velocity=GetInitialvelocity();
        }
        else if (ActionNow->GetCurrentFrameIndex() <3) {
            velocity.x += velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else if (ActionNow->GetCurrentFrameIndex() <5) {
            velocity.x -= velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else {
            ResetVelocity();
        }
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Vega::PsychoCrusherStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::punch);
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Vega::PsychoCrusherStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex() <=2) {
            ResetVelocity();
        }
        else if (ActionNow->GetCurrentFrameIndex() ==3) {
            velocity=GetInitialvelocity();
        }
        else if (ActionNow->GetCurrentFrameIndex() <=5) {
            velocity.x += velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else if (ActionNow->GetCurrentFrameIndex() <= 7) {
            velocity.x -= velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else {
            ResetVelocity();
        }
        if (GetAnimationIsEnd()) {ClearButtonType();ChangeState(FighterState::Idle);}
    }
    void Vega::HeadStompStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::kick);
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Vega::HeadStompStateUpdate() {
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if(ActionNow->GetCurrentFrameIndex()>=2) {
            if(controller->IsKeyDown(Keys::LK)||controller->IsKeyDown(Keys::MK)||controller->IsKeyDown(Keys::HK)) {
                ChangeState(FighterState::Special_4);
            }
        }
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ClearButtonType();ChangeState(FighterState::Idle);}
    }
    void Vega::HeadStompAttackStateEnter() {
        direction=GetNewDirection();
        PlayCurrentSound();
        velocity.x=0;
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Vega::HeadStompAttackStateUpdate() {
        velocity.y += Gravity * 2 * Time::GetDeltaTimeMs()/1000;
        if (HitEnemy) {ChangeState(FighterState::SpecialRecovery_4);}
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ClearButtonType();ChangeState(FighterState::Idle);}
    }
    void Vega::HeadStompRecoveryStateEnter() {
        ResetVelocity();
        velocity=GetInitialvelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Vega::HeadStompRecoveryStateUpdate() {
        if(GetCharacterIsOnFloor()&&velocity.y<0){velocity.y=0;}
        else{velocity.y+=Gravity*Time::GetDeltaTimeMs()/1000;}
        if(ActionNow->GetCurrentFrameIndex()>=2) {
            if(controller->IsKeyDown(Keys::LP)||controller->IsKeyDown(Keys::MP)||controller->IsKeyDown(Keys::HP)) {
                ChangeState(FighterState::SpecialDerive_4);
            }
        }
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }
    void Vega::HeadStompDeriveStateEnter() {
        velocity.x=0;
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Vega::HeadStompDeriveStateUpdate() {
        velocity.y += Gravity * Time::GetDeltaTimeMs()/1000;
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }
}