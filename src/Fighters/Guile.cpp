//
// Created by asus on 2025/2/27.
//

#include "Fighters/Guile.hpp"
namespace Util {
    Guile::Guile():Fighter("Guile"){
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/GuileTheme.mp3");
        country_position={{350, 140},0,{1,1}};
        BackgroundInit(5);
        StateInit();
        LoadCommonVelocities();
        Guile::LoadAnimations();
        Guile::LoadOffsetVelocity();
        Guile::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Guile::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(6,"Idle");
        animations[FighterState::Backward] = ActionInit(5,"Backward");
        animations[FighterState::Forward] = ActionInit(5,"Forward");
        animations[FighterState::JumpUP] = ActionInit(10, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(8, "JumpForward");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(3, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::HP] = ActionInit(5, "HP");
        animations[FighterState::LK] = ActionInit(3, "LK");
        animations[FighterState::MK] = ActionInit(6, "MK");
        animations[FighterState::HK] = ActionInit(6, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::BackwardBlock]=ActionInit(3, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(3, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(4, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(5, "CrouchHP");
        animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");
        animations[FighterState::CrouchMK] = ActionInit(5, "CrouchMK");
        animations[FighterState::CrouchHK] = ActionInit(11, "CrouchHK");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(3, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(2, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100, 100, 100, 100, 100, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,60,60,60,60,60,60,60,60,60};
        frames[FighterState::JumpForward]={60,60,60,60,60,60,60,60};
        frames[FighterState::JumpBackward]={60,60,60,60,60,60,60,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60,60};
        frames[FighterState::CrouchUp]={60,60,60};
        frames[FighterState::LP]={60,60,60};
        frames[FighterState::MP]={60,60,60,60,60};
        frames[FighterState::HP]={60,60,60,60,60};
        frames[FighterState::LK]={60,60,60};
        frames[FighterState::MK]={60,60,60,60,60,60};
        frames[FighterState::HK]={60,60,60,60,60,60};

        frames[FighterState::CrouchLP]={60,90,60};
        frames[FighterState::CrouchMP]={60,60,60,60};
        frames[FighterState::CrouchHP]={60,60,60,60,60};
        frames[FighterState::CrouchLK]={60,60,60};
        frames[FighterState::CrouchMK]={60,60,60,60,60};
        frames[FighterState::CrouchHK]={60,60,60,60,60,60,60,60,60,60,60};

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150,150};
        frames[FighterState::CrouchBlock] = {150,150};

        frames[FighterState::WinStart]={10};
        frames[FighterState::Win]={200, 200, 200};

        frames[FighterState::TimeOverLoss]={180, 180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Guile::LoadOffsetVelocity() {
        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Crouch]={{11,-43}};
        offset[FighterState::CrouchDown]={{10,-9},{11,-30},{11,-30}};
        offset[FighterState::CrouchUp]={{11,-30},{11,-30},{10,-9}};
        //Stand attack offset
        offset[FighterState::LP]={{28,3},{74,5},{40,1}};
        offset[FighterState::MP]={{27,-27},{18,-17},{18,30},{16,6},{19,-18}};
        offset[FighterState::HP]={{-17,16},{24,12},{93,11},{227,8},{95,0}};
        offset[FighterState::LK]={{-3,6},{3,2},{91,1}};
        offset[FighterState::MK]={{-18,16},{-24,18},{31,12},{60,1},{116,-8},{51,-9}};
        offset[FighterState::HK]={{-5,14},{57,14},{107,14},{55,23},{87,14},{14,19}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{1,-33},{49,-35},{49,-35}};
        offset[FighterState::CrouchMP]={{34,-48},{55,-51},{39,-50},{31,-48}};
        offset[FighterState::CrouchHP]={{2,-30},{17,-19},{25,6},{5,62},{25,8}};
        offset[FighterState::CrouchLK]={{24,-47},{24,-47},{93,-57}};
        offset[FighterState::CrouchMK]={{-87,-58},{-51,-42},{24,-59},{-42,-42},{-37,-42}};
        offset[FighterState::CrouchHK]={{19,-42},{105,-51},{163,-50},{130,-51},{86,-47},{55,-49},{55,-63},{88,-43},{160,-60},{94,-40},{87,-40}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::BackwardBlock]={{-8,-4},{-9,-23},{11,-8}};
        offset[FighterState::CrouchBlock]={{-18,-32},{-24,-30}};

        offset[FighterState::Win]={{-24,52},{-29,45},{-26,34}};
        offset[FighterState::WinStart]={{-25,52}};

        offset[FighterState::TimeOverLoss]={{24,33},{24,33}};
        offset[FighterState::DefeatedLoss]={{-73,7},{-153,-46},{-262,-103}};
    }
    void Guile::LoadAllBox() {

        boxes.pushbox.size[FighterState::Idle]={100,200};
        boxes.pushbox.offset[FighterState::Idle]={15,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={100,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={15,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{100,100},{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{100,125},{100,125},{100,125},{100,125},{100,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{23,113},{28,110},{27,109},{26,117},{25,116},{25,116}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-15,57},{-15,57},{-10,55},{-10,54},{-12,53},{-12,53}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-12,-53},{-12,-52},{-12,-52},{-12,-52},{-11,-48},{-11,-48}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{140,70}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{150,60}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{20,66}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{-1,2}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{-2,-71}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{140,70},{140,70},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{140,130},{140,80},{150,60}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{20,101},{22,44},{20,66}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{-14,60},{0,1},{-1,2}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-19,-55},{-4,-74},{-2,-71}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{140,70},{140,70},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{150,60},{140,80},{140,130}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{20,66},{22,44},{20,101}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{-1,2},{0,1},{-14,60}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{-2,-71},{-4,-74},{-19,-55}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{100,60},{100,60}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{110,70},{120,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{5,79},{-30,72}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{4,10},{-25,27}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{11,-55},{-8,-44}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{3,91},{-3,60},{-25,58}};
        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{100,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{120,70},{120,70},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{12,66},{14,63},{29,64}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-9,14},{5,13},{-3,11}};

        boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]={{100,70},{100,70},{120,60}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]={{120,70},{100,70},{160,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]={{-29,70},{-78,55},{-69,48}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-37,22},{-69,17},{-44,7}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{-17,-46},{-13,-47},{-30,-56}};

        boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMP]={{100,70},{120,70},{110,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMP]={{120,70},{120,70},{120,70},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMP]={{2,61},{5,61},{0,59},{-4,59}};
        boxes.hurtbox.body.offset[FighterState::CrouchMP]={{-39,23},{-25,23},{-42,23},{-40,24}};

        boxes.hurtbox.head.size[FighterState::CrouchMK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMK]={{100,70},{120,70},{130,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMK]={{120,70},{150,70},{120,70},{150,70},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMK]={{-41,56},{-37,77},{-20,63},{-33,75},{0,75}};
        boxes.hurtbox.body.offset[FighterState::CrouchMK]={{9,24},{-19,23},{27,26},{-15,23},{6,26}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]={{19,-33},{14,-32},{36,-41},{5,-39},{24,-40}};

        boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]={{100,70},{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]={{120,70},{120,100},{110,125},{110,140},{120,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]={{39,75},{60,101},{39,150},{-11,180},{39,153}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]={{14,25},{42,44},{34,84},{2,125},{38,85}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{-9,-47},{5,-50},{24,-22},{-6,-3},{21,-26}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]={{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{100,70},{110,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]={{120,60},{100,60},{140,60},{130,60},{120,60},{120,60},{120,50},{140,50},{150,50},{140,60},{120,60}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]={{-31,64},{1,48},{7,48},{7,50},{11,52},{-6,50},{-4,36},{-2,60},{7,50},{-9,67},{15,63}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]={{-33,17},{24,8},{41,9},{39,9},{49,13},{49,12},{37,-2},{9,6},{34,-1},{17,15},{21,13}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{-11,-49},{71,-57},{24,-56},{16,-61},{39,-62},{58,-60},{54,-61},{43,-56},{38,-60},{14,-54},{34,-56}};
        //hurtbox Stand Attack

        boxes.hurtbox.head.offset[FighterState::LP]={{17,103},{17,106},{16,104}};
        boxes.hurtbox.body.offset[FighterState::LP]={{-18,56},{-22,58},{-19,53}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-12,-53},{-12,-52},{-12,-52}};

        boxes.hurtbox.head.offset[FighterState::MP]={{83,83},{10,103},{32,113},{27,113},{17,103}};
        boxes.hurtbox.body.offset[FighterState::MP]={{37,45},{13,57},{32,59},{30,65},{20,59}};
        boxes.hurtbox.leg.size[FighterState::MP]={{150,100},{150,100},{150,100},{150,100},{150,100}};
        boxes.hurtbox.leg.offset[FighterState::MP]={{-2,-53},{-2,-52},{-2,-52},{-2,-52},{-2,-48},{-2,-48}};

        boxes.hurtbox.head.offset[FighterState::HP]={{-29,116},{31,107},{136,112},{188,105},{89,89}};
        boxes.hurtbox.body.offset[FighterState::HP]={{-17,61},{45,51},{140,63},{185,56},{86,43}};
        boxes.hurtbox.leg.size[FighterState::HP]={{120,130},{120,120},{100,120},{150,120},{130,120}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{-4,-54},{36,-54},{101,-44},{191,-64},{124,-54}};

        boxes.hurtbox.head.offset[FighterState::LK]={{28,115},{23,111},{8,108}};
        boxes.hurtbox.body.offset[FighterState::LK]={{22,63},{20,63},{6,69}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{22,-37},{23,-41},{19,-44}};

        boxes.hurtbox.head.offset[FighterState::MK]={{-25,115},{-15,119},{74,111},{83,89},{39,50},{42,65}};
        boxes.hurtbox.body.size[FighterState::MK]={{90,80},{80,80},{80,70},{110,70},{110,80},{110,80}};
        boxes.hurtbox.body.offset[FighterState::MK]={{-21,57},{12,70},{81,70},{95,48},{44,10},{32,17}};
        boxes.hurtbox.leg.size[FighterState::MK]={{120,130},{120,120},{90,140},{90,130},{130,120},{100,130}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{5,-66},{12,-50},{85,-36},{91,-51},{83,-83},{79,-85}};

        boxes.hurtbox.head.offset[FighterState::HK]={{15,118},{4,115},{-1,107},{1,109},{45,115},{10,113}};
        boxes.hurtbox.body.size[FighterState::HK]={{90,80},{80,70},{90,70},{110,70},{120,80},{120,80}};
        boxes.hurtbox.body.offset[FighterState::HK]={{16,65},{24,78},{23,63},{20,73},{74,76},{20,63}};
        boxes.hurtbox.leg.size[FighterState::HK]={{110,160},{80,160},{70,160},{75,160},{70,160},{110,160}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{21,-55},{60,-45},{70,-47},{67,-47},{109,-43},{41,-38}};
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={143,50};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{128,44},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMP]={140,50};
        boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{108,34},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]={50,180};
        boxes.hitbox.offset[FighterState::CrouchHP]={{-1,-1},{-1,-1},{145,132},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchLK]={240,60};
        boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{-1,-1},{158,-21}};
        boxes.hitbox.size[FighterState::CrouchMK]={240,60};
        boxes.hitbox.offset[FighterState::CrouchMK]={{-1,-1},{-1,-1},{202,-19},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHK]={240,60};
        boxes.hitbox.offset[FighterState::CrouchHK]={{-1,-1},{-1,-1},{236,-18},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{235,-42},{-1,-1},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={140,50};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{129,85},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={60,160};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{75,89},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={150,50};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{-1,-1},{335,85},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={200,70};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{170,-24}};
        boxes.hitbox.size[FighterState::MK]={200,60};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{245,-30},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={140,80};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{-1,-1},{200,115},{-1,-1},{-1,-1},{-1,-1}};
    }
}