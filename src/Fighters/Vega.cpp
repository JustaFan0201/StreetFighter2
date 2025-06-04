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
        animations[FighterState::HK] =animations[FighterState::MK] =animations[FighterState::LK] = ActionInit(5, "LK");

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
        frames[FighterState::MK]={60,80,100,80,60};
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
        offset[FighterState::LP]={{-4,-14},{25,-5},{26,-3},{26,-3},{26,-5},{-5,-15},{-7,-12}};
        offset[FighterState::HP]=offset[FighterState::MP]={{-32,-11},{-49,-20},{-50,-17},{-9,-25},{-8,-26},{-8,-23},{-8,-26},{-32,-9},{-33,-10}};
        offset[FighterState::HK] = offset[FighterState::MK]=offset[FighterState::LK]={{13,5},{84,14},{239,13},{84,14},{13,5}};
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

        boxes.hurtbox.head.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchLK]={{120,70},{110,70},{120,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchLK]={{170,90},{190,80},{170,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchLK]={{-7,70},{-82,67},{-7,70}};
        boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-6,36},{-65,20},{-6,36}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{13,-50},{-22,-52},{13,-50}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]={{120,70},{110,80},{120,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]={{100,160},{140,120},{170,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]={{-45,110},{-71,80},{6,27}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]={{-28,66},{-68,27},{7,-12}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{-63,-62},{-7,-70},{14,-91}};

         //hurtbox Stand Attack
        boxes.hurtbox.head.offset[FighterState::LP]={{1,105},{20,120},{20,120},{20,120},{20,120},{3,99},{2,103}};
        boxes.hurtbox.body.offset[FighterState::LP]={{-29,63},{-10,73},{-10,73},{-10,73},{-10,73},{-32,54},{-32,54}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-32,-56},{-23,-55},{-23,-56},{-23,-56},{-23,-56},{-24,-63},{-23,-60}};

        boxes.hurtbox.head.offset[FighterState::HP]=boxes.hurtbox.head.offset[FighterState::MP]={{16,108},{16,89},{17,92},{35,81},{39,81},{39,81},{39,81},{18,107},{17,107}};
        boxes.hurtbox.body.offset[FighterState::HP]=boxes.hurtbox.body.offset[FighterState::MP]={{-20,55},{-26,44},{-28,49},{-20,51},{-15,48},{-11,50},{-8,51},{-13,60},{-10,60}};
        boxes.hurtbox.leg.size[FighterState::HP]=boxes.hurtbox.leg.size[FighterState::MP]={{160,130},{150,110},{150,110},{140,100},{140,100},{140,100},{140,100},{170,120},{170,120}};
        boxes.hurtbox.leg.offset[FighterState::HP]=boxes.hurtbox.leg.offset[FighterState::MP]={{2,-58},{-11,-64},{-11,-64},{-14,-57},{-20,-56},{-18,-54},{-19,-53},{-4,-58},{-3,-60}};

        boxes.hurtbox.head.offset[FighterState::HK]=boxes.hurtbox.head.offset[FighterState::MK]=boxes.hurtbox.head.offset[FighterState::LK]={{5,117},{35,132},{119,133},{34,133},{7,117}};
        boxes.hurtbox.body.offset[FighterState::HK]= boxes.hurtbox.body.offset[FighterState::MK]=boxes.hurtbox.body.offset[FighterState::LK]={{5,51},{26,87},{87,76},{26,87},{5,51}};
        boxes.hurtbox.leg.size[FighterState::HK]= boxes.hurtbox.leg.size[FighterState::MK]=boxes.hurtbox.leg.size[FighterState::LK]={{160,140},{120,160},{80,160},{120,160},{160,140}};
        boxes.hurtbox.leg.offset[FighterState::HK]=boxes.hurtbox.leg.offset[FighterState::MK]=boxes.hurtbox.leg.offset[FighterState::LK]={{22,-72},{62,-49},{142,-29},{62,-49},{22,-72}};

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
        boxes.hurtbox.head.offset[FighterState::JumpLK]={{80,107},{36,28}};
        boxes.hurtbox.body.offset[FighterState::JumpLK]={{119,64},{51,-18}};
        boxes.hurtbox.leg.offset[FighterState::JumpLK]={{126,-32},{94,-92}};

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
        boxes.hitbox.size[FighterState::CrouchMK]=boxes.hitbox.size[FighterState::CrouchLK]={265,60};
        boxes.hitbox.offset[FighterState::CrouchMK]=boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{83,-46},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHK]={250,100};
        boxes.hitbox.offset[FighterState::CrouchHK]={{-1,-1},{61,-66},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={175,60};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{125,110},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]=boxes.hitbox.size[FighterState::MP]={140,70};
        boxes.hitbox.offset[FighterState::HP]=boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{-1,-1},{110,34},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]=boxes.hitbox.size[FighterState::MK]=boxes.hitbox.size[FighterState::LK]={260,60};
        boxes.hitbox.offset[FighterState::HK]=boxes.hitbox.offset[FighterState::MK]=boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{300,56},{-1,-1},{-1,-1}};
        //hitbox Jump Attack
        boxes.hitbox.size[FighterState::JumpHP]=boxes.hitbox.size[FighterState::JumpMP]=boxes.hitbox.size[FighterState::JumpLP]={220,50};
        boxes.hitbox.offset[FighterState::JumpHP]=boxes.hitbox.offset[FighterState::JumpMP]=boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{110,44},{-1,-1}};
        boxes.hitbox.size[FighterState::JumpLK]={150,190};
        boxes.hitbox.offset[FighterState::JumpLK]={{-1,-1},{65,44}};
        boxes.hitbox.size[FighterState::JumpMK]={240,70};
        boxes.hitbox.offset[FighterState::JumpMK]={{-1,-1},{-1,-1},{200,-84}};
        boxes.hitbox.size[FighterState::JumpHK]={260,70};
        boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{140,-60},{-1,-1}};
    }
    void Vega::LoadSpecialMove() {

    }
}