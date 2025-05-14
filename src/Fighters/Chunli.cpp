//
// Created by asus on 2025/2/27.
//

#include "Fighters/Chunli.hpp"
namespace Util {
    Chunli::Chunli(): Fighter("Chunli") {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Chunli/Chunli_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Chunli/Chunli_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/china.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/china_dark.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/ChunliTheme.mp3");
        country_position={{-113, 193},0,{1,1}};
        face_postion={{-53, -253},0,{1,1}};
        BackgroundInit(29);
        StateInit();
        LoadCommonVelocities();
        Chunli::LoadAnimations();
        Chunli::LoadOffsetVelocity();
        Chunli::LoadAllBox();
        Chunli::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Chunli::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Chunli::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(4,"Idle");
        animations[FighterState::Backward] = ActionInit(12,"Backward");
        animations[FighterState::Forward] = ActionInit(12,"Forward");
        animations[FighterState::JumpUP] = ActionInit(9, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(11, "JumpForward");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(3, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;
        animations[FighterState::LP] = ActionInit(5, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::HP] = ActionInit(5, "HP");
        animations[FighterState::LK] = ActionInit(5, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(6, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(5, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(5, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(5, "CrouchHP");
        animations[FighterState::CrouchLK] = ActionInit(5, "CrouchLK");
        animations[FighterState::CrouchMK] = ActionInit(3, "CrouchMK");
        animations[FighterState::CrouchHK] = ActionInit(5, "CrouchHK");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(5, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(3, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100, 150, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,60,60,60,60,60,60,60,60};
        frames[FighterState::JumpForward]={60,60,60,60,60,60,60,60,60,60,60};
        frames[FighterState::JumpBackward]={60,60,60,60,60,60,60,60,60,60,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={120,60,60};
        frames[FighterState::CrouchUp]={60,120};
        frames[FighterState::LP]={60,60,60,60,60};
        frames[FighterState::MP]={60,60,60,60,60};
        frames[FighterState::HP]={60,60,60,60,60};
        frames[FighterState::LK]={60,60,60,60,60};
        frames[FighterState::MK]={60,60,60,60,60};
        frames[FighterState::HK]={60,60,60,60,60,60};

        frames[FighterState::CrouchLP]={60,60,60,60,60};
        frames[FighterState::CrouchMP]={60,60,60,60,60};
        frames[FighterState::CrouchHP]={60,60,60,60,60};
        frames[FighterState::CrouchLK]={60,60,60,60,60};
        frames[FighterState::CrouchMK]={60,60,60};
        frames[FighterState::CrouchHK]={60,60,60,60,60};

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150};
        frames[FighterState::CrouchBlock] = {150,150};

        frames[FighterState::WinStart]={200};
        frames[FighterState::Win]={200, 200, 200, 200, 200};

        frames[FighterState::TimeOverLoss]={180, 180,180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Chunli::LoadOffsetVelocity() {
        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Crouch]={{-3,-29}};
        offset[FighterState::CrouchDown]={{-15,-11},{-4,-22},{-3,-29}};
        offset[FighterState::CrouchUp]={{-3,-29},{-4,-22},{-15,-11}};
        //Stand attack offset
        offset[FighterState::LP]={{-15,0},{6,4},{-22,12},{3,0},{-12,0}};
        offset[FighterState::MP]={{60,-4},{89,-7},{124,-11},{89,-7},{62,-4}};
        offset[FighterState::HP]={{44,-5},{75,-14},{94,-17},{77,-15},{42,-7}};
        offset[FighterState::LK]={{-41,0},{-49,10},{45,13},{-53,8},{-43,5}};
        offset[FighterState::MK]={{-29,7},{-43,11},{-12,15},{-12,15},{-36,11}};
        offset[FighterState::HK]={{{-10,-19},{11,2},{18,3},{70,11},{39,-6},{-3,-10}}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{0,-32},{4,-30},{60,-38},{5,-34},{2,-35}};
        offset[FighterState::CrouchMP]={{4,-27},{38,-28},{102,-27},{38,-27},{6,-31}};
        offset[FighterState::CrouchHP]={{7,-31},{46,-33},{84,-30},{45,-30},{7,-30}};
        offset[FighterState::CrouchLK]={{-10,-42},{-53,-43},{4,-54},{-47,-43},{-10,-41}};
        offset[FighterState::CrouchMK]={{-73,-38},{0,-44},{-28,-45}};
        offset[FighterState::CrouchHK]={{-27,-29},{4,-32},{83,-23},{4,-34},{-24,-33}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::BackwardBlock]={{-3,3},{1,5}};
        offset[FighterState::CrouchBlock]={{35,-44},{16,-38}};

        offset[FighterState::Win]={{-5,25},{-4,84},{2,106},{2,132},{2,106}};
        offset[FighterState::WinStart]={{14,17}};

        offset[FighterState::TimeOverLoss]={{17,19},{15,18},{14,12}};
        offset[FighterState::DefeatedLoss]={{-212,-2},{-192,-36},{-201,-100}};
    }
    void Chunli::LoadAllBox() {

        boxes.pushbox.size[FighterState::Idle]={100,200};
        boxes.pushbox.offset[FighterState::Idle]={-20,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={100,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={15,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{100,125},{100,125},{100,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{-17,95},{-15,94},{-15,96},{-12,95}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-46,44},{-44,47},{-45,52},{-45,48}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-39,-45},{-40,-48},{-42,-49},{-42,-47}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{120,70}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{150,70}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{20,60}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{4,16}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{15,-57}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{120,70},{120,70},{120,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{140,100},{140,80},{150,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{-5,87},{24,62},{20,60}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{-32,45},{0,19},{4,16}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-20,-53},{13,-57},{15,-57}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{120,70},{120,70},{120,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{150,70},{140,80},{140,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{20,60},{24,62},{-5,87}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{4,16},{0,19},{-32,45}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{15,-57},{13,-57},{-20,-53}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{150,70},{150,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{-15,71},{-63,76}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{-28,25},{-67,29}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{-1,-49},{-21,-43}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{-33,95},{-54,97}};
        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{140,70},{140,70},{140,70},{140,70},{140,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{31,65},{34,70},{51,58},{38,63},{34,63}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{8,22},{11,21},{19,18},{9,17},{4,15}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLP]={{11,-52},{11,-48},{18,-54},{3,-51},{9,-52}};

        boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]={{100,50},{100,50},{120,30},{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]={{140,60},{140,50},{160,60},{140,50},{140,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]={{0,57},{-50,53},{-38,28},{-40,55},{3,60}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-14,18},{-65,17},{-63,-6},{-65,14},{-19,18}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{-6,-43},{-58,-30},{-52,-41},{-51,-26},{-18,-36}};

        boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMP]={{100,70},{100,70},{110,80},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMP]={{170,70},{170,70},{170,70},{170,70},{170,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMP]={{66,67},{84,64},{114,67},{83,66},{65,63}};
        boxes.hurtbox.body.offset[FighterState::CrouchMP]={{35,17},{57,17},{78,20},{52,17},{35,13}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMP]={{15,-50},{28,-52},{45,-50},{30,-50},{18,-53}};

        boxes.hurtbox.head.size[FighterState::CrouchMK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMK]={{70,60},{90,60},{70,60}};
        boxes.hurtbox.leg.size[FighterState::CrouchMK]={{120,70},{150,70},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMK]={{-79,61},{-25,48},{0,58}};
        boxes.hurtbox.body.offset[FighterState::CrouchMK]={{-43,21},{-18,12},{-21,15}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]={{-6,-42},{11,-46},{2,-48}};

        boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]={{100,60},{100,60},{100,60},{100,60},{100,60}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]={{160,70},{160,70},{160,80},{160,70},{160,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]={{65,67},{87,64},{115,67},{87,68},{63,68}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]={{36,19},{60,21},{79,30},{56,23},{34,22}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{9,-44},{36,-52},{40,-48},{39,-43},{31,-45}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]={{100,70},{100,70},{130,90},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]={{100,70},{120,70},{40,70},{120,70},{100,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]={{-57,62},{-42,59},{-40,50},{-43,56},{-60,55}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]={{-34,27},{3,28},{50,30},{3,28},{-34,27}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{-32,-37},{-5,-45},{-24,-42},{-5,-45},{-32,-37}};
        //hurtbox Stand Attack
        boxes.hurtbox.head.offset[FighterState::LP]={{9,96},{7,101},{33,108},{2,99},{10,97}};
        boxes.hurtbox.body.offset[FighterState::LP]={{-13,43},{-9,44},{18,55},{-17,44},{-14,42}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-27,-53},{-23,-54},{-4,-55},{-23,-58},{-8,-59}};

        boxes.hurtbox.head.offset[FighterState::MP]={{-4,92},{45,82},{78,79},{45,84},{-3,90}};
        boxes.hurtbox.body.offset[FighterState::MP]={{-15,46},{31,37},{58,30},{25,35},{-15,41}};
        boxes.hurtbox.leg.size[FighterState::MP]={{140,100},{140,100},{140,100},{140,100},{140,100}};
        boxes.hurtbox.leg.offset[FighterState::MP]={{-1,-49},{28,-50},{58,-60},{30,-54},{-5,-48}};

        boxes.hurtbox.head.offset[FighterState::HP]={{0,91},{49,75},{91,75},{51,74},{-3,88}};
        boxes.hurtbox.body.offset[FighterState::HP]={{-21,46},{29,28},{79,34},{17,31},{-29,45}};
        boxes.hurtbox.leg.size[FighterState::HP]={{140,120},{140,100},{140,120},{140,120},{140,120}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{-18,-57},{22,-61},{56,-64},{29,-67},{-14,-57}};

        boxes.hurtbox.head.offset[FighterState::LK]={{-14,99},{-19,115},{3,125},{-23,111},{-16,105}};
        boxes.hurtbox.body.offset[FighterState::LK]={{-33,53},{-36,66},{-3,75},{-40,52},{-35,53}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{-25,-36},{-41,-43},{-1,-55},{-36,-51},{-27,-39}};

        boxes.hurtbox.head.offset[FighterState::MK]={{-10,99},{-23,108},{-69,118},{9,113},{-20,105}};
        boxes.hurtbox.body.offset[FighterState::MK]={{-31,55},{-45,63},{-61,71},{-9,63},{-40,56}};
        boxes.hurtbox.leg.size[FighterState::HK]={{140,120},{140,100},{140,120},{140,120},{140,120}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{-25,-47},{-35,-50},{-33,-29},{-15,-46},{-30,-45}};

        boxes.hurtbox.head.offset[FighterState::HK]={{-6,41},{-52,50},{-67,67},{-74,82},{-69,86},{-66,105}};
        boxes.hurtbox.body.size[FighterState::HK]={{70,70},{100,70},{140,70},{140,70},{120,70},{70,100}};
        boxes.hurtbox.body.offset[FighterState::HK]={{17,53},{33,53},{38,61},{21,69},{13,68},{-37,81}};
        boxes.hurtbox.leg.size[FighterState::HK]={{140,120},{50,130},{50,140},{70,140},{80,120},{140,140}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{7,-45},{59,-37},{66,-37},{71,-34},{53,-27},{20,-20}};
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={145,40};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{-1,-1},{147,21},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMP]={150,40};
        boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{210,33},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]={150,40};
        boxes.hitbox.offset[FighterState::CrouchHP]={{-1,-1},{-1,-1},{210,34},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchLK]={170,50};
        boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{-1,-1},{88,-60},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMK]={175,60};
        boxes.hitbox.offset[FighterState::CrouchMK]={{-1,-1},{158,-46},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHK]={220,100};
        boxes.hitbox.offset[FighterState::CrouchHK]={{-1,-1},{-1,-1},{192,48},{-1,-1},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={150,40};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{97,81},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={165,40};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{194,47},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={130,50};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{180,78},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={180,50};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{155,43},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MK]={180,60};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{91,100},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={140,95};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{-1,-1},{-1,-1},{196,130},{-1,-1},{-1,-1},{-1,-1}};
    }
    void Chunli::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(12, "Special_1");
        offset[FighterState::Special_1]={{-40,6},{-38,11},{-25,21},{0,26},{-6,15},{19,14},{-2,11},{43,14},{-31,11},{18,13},{-41,12},{-41,7}};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LK]={60,90,120,60,120,60,120,60,120,60,90,60};
        boxes.hurtbox.head.size[FighterState::Special_1]={{80,70},{80,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{80,70},{80,70}};
        boxes.hurtbox.body.size[FighterState::Special_1]={{100,150},{150,150},{50,150},{50,150},{50,150},{50,150},{50,150},{50,150},{50,150},{50,150},{100,150},{150,150}};

        boxes.hurtbox.head.offset[FighterState::Special_1]={{-10,100},{-6,109},{-69,117},{-68,118},{-68,118},{-68,118},{-57,111},{-66,118},{-61,113},{-67,118},{-9,112},{-9,101}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{-34,49},{-28,56},{-61,62},{-61,62},{-61,62},{-61,62},{-61,62},{-63,63},{-54,61},{-62,62},{-33,58},{-38,53}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{-11,-45},{-1,-41},{-43,-42},{-42,-41},{-42,-41},{-42,-41},{-42,-41},{-44,-43},{-40,-42},{-47,-46},{-1,-41},{-12,-46}};
        boxes.hitbox.size[FighterState::Special_1]={200,100};
        boxes.hitbox.offset[FighterState::Special_1]={{-1,-1},{-1,-1},{90,110},{-1,-1},{102,17},{-1,-1},{102,49},{-1,-1},{72,-10},{-1,-1},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::LK]=8;

        SpecialMoveData.attackdata[FighterState::Special_1].HitStrength[Keys::LK]=HitStrength::H;

        StateEnter[FighterState::Special_1]=[this] { HyakurretsuKyakuStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { HyakurretsuKyakuStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Chunli/SP1.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={};
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ALL_KICK;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Null;

        animations[FighterState::Special_2]=ActionInit(23, "Special_2");
        offset[FighterState::Special_2]={{6,-8},{-51,33},{40,29},{88,34},{72,49},{75,52},{83,43},{76,51},{47,27},{-20,20},{57,14},{80,14},{25,13},{10
,13},{45,9},{120,13},{76,51},{83,43},{75,52},{59,51},{100,48},{44,49},{-52,35}};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LK]={30,30,30,30,30,60,60,60,60,60,60,120,60,60,60,120,75,60,60,30,30,30,30};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::MK]={30,30,30,30,30,60,60,60,75,75,75,150,75,75,75,150,90,75,60,30,30,30,30};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::HK]={30,30,30,30,30,60,60,60,90,90,90,180,90,90,90,240,120,90,60,30,30,30,30};

        boxes.hurtbox.body.size[FighterState::Special_2]={{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::Special_2]={{150,125},{100,150},{100,125},{200,100},{150,100},{100,150},{100,150},{100,150},{100,50},{100,50},{100,50},{100,50},{100,50},{100,50},{100,50},{100,50},{100,150},{100,150},{100,150},{100,150},{150,125}};
        boxes.hurtbox.head.offset[FighterState::Special_2]={{-4,90},{-70,171},{118,98},{224,11},{179,-42},{69,-42},{84,-59},{72,-41},{18,-49},{-22,-54},{70,-67},{86,-53},{37
,-51},{4,-52},{20,-53},{101,-53},{70,-42},{81,-59},{74,-43},{165,-42},{235,31},{121,119},{-70,174}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{-25,39},{-70,118},{61,109},{185,49},{153,11},{81,13},{86,-9},{82,10},{28,12},{-23,5},{64,-10},{82,5},{38,0},{3,2
},{20,0},{103,6},{79,10},{86,-8},{78,9},{136,19},{189,66},{65,134},{-71,124}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{-4,-53},{-56,6},{-17,37},{39,42},{54,91},{84,122},{91,99},{85,119},{24,81},{-13,76},{70,71},{84,71},{30,68},{-2,
68},{4,68},{91,68},{80,115},{85,98},{77,116},{37,94},{50,56},{-18,55},{-56,0}};
        boxes.hitbox.size[FighterState::Special_2]={350,100};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{76,73},{-1,-1},{-1,-1},{-1,-1},{99,72},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

        StateEnter[FighterState::Special_2]=[this] { SpinningBirdKickStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { SpinningBirdKickStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Chunli/SP2.wav");

        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::LK]={9,0};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::MK]={12,0};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::HK]={15,0};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LK]=5;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::MK]=8;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::HK]=10;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LK]=HitStrength::H;

        SpecialMoveData.SkillCommand[FighterState::Special_2].command={
            SpecialMoveDirection::Up,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_2].requiredAttack=AttackButton::ANY_KICK;
        SpecialMoveData.SkillCommand[FighterState::Special_2].commandtype=CommandType::Pressed;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::LK]=250;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::MK]=500;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::HK]=750;
        SpecificStates.InvincibleForFlyObj.insert(FighterState::Special_2);
        SpecificStates.borderCheckStates.insert(FighterState::Special_2);

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Chunli/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Chunli/Loss.wav");
    }
    void Chunli::HyakurretsuKyakuStateEnter() {
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Chunli::HyakurretsuKyakuStateUpdate() {
        if (GetAnimationIsEnd()) {ClearButtonType();ChangeState(FighterState::Idle);}
    }
    void Chunli::SpinningBirdKickStateEnter() {
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Chunli::SpinningBirdKickStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex() > 8&&ActionNow->GetCurrentFrameIndex() <= 11) {
            velocity.x += velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else if (ActionNow->GetCurrentFrameIndex() >= 12&&ActionNow->GetCurrentFrameIndex() <= 15) {
            velocity.x -= velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
        }
        else if (ActionNow->GetCurrentFrameIndex() == 8) {
            velocity=GetInitialvelocity();
        }
        else {
            ResetVelocity();
        }
        if (GetAnimationIsEnd()) {ClearButtonType();ChangeState(FighterState::Idle);}
    }
}