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
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
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

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(6, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(8, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(6, "CrouchHP");
        animations[FighterState::CrouchLK] = ActionInit(3, "CrouchLK");
        animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK];
        animations[FighterState::CrouchHK] = ActionInit(6, "CrouchHK");

        frames[FighterState::Idle]={150, 150, 150};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120, 120, 120};
        frames[FighterState::JumpForward]={60,90,120,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,120,90,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={120,60};
        frames[FighterState::CrouchUp]={60,120};
        frames[FighterState::LP]={30,60,60,60,60,30};
        frames[FighterState::MP]={60,60,60,60};
        frames[FighterState::HP]={60,60,60,60,60,60};
        frames[FighterState::LK]={60,60,60,60,60,60};
        frames[FighterState::MK]={60,60,60,60,60,60};
        frames[FighterState::HK]={60,60,60,60,60,60,60};

        frames[FighterState::CrouchLP]={60,60,60,60,60,60};
        frames[FighterState::CrouchMP]={60,60,60,60,60,60,60,60};
        frames[FighterState::CrouchHP]={60,60,60,60,60,60};
        frames[FighterState::CrouchLK]={60,60,60};
        frames[FighterState::CrouchMK]={60,60,60};
        frames[FighterState::CrouchHK]={60,60,60,60,60,60};

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150};
        frames[FighterState::CrouchBlock] = {150,150};
    }
    void Blanka::LoadOffsetVelocity() {
        Initialvelocity.x[FighterState::Forward]=8;
        Initialvelocity.x[FighterState::Backward]=-8;
        Initialvelocity.x[FighterState::JumpForward]=10;
        Initialvelocity.x[FighterState::JumpBackward]=-10;
        Initialvelocity.y[FighterState::JumpForward]=38;
        Initialvelocity.y[FighterState::JumpBackward]=38;
        Initialvelocity.y[FighterState::JumpUP]=38;

        Initialvelocity.x[FighterState::HurtBodyL]=Initialvelocity.x[FighterState::HurtHeadL]=-6;
        Initialvelocity.x[FighterState::HurtBodyM]=Initialvelocity.x[FighterState::HurtHeadM]=-8;
        Initialvelocity.x[FighterState::HurtBodyH]=Initialvelocity.x[FighterState::HurtHeadH]=-10;

        Initialvelocity.x[FighterState::BackwardBlock]=Initialvelocity.x[FighterState::CrouchBlock]=-4;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0}};
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

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::BackwardBlock]={{-3,3},{1,5}};
        offset[FighterState::CrouchBlock]={{35,-44},{16,-38}};
    }
    void Blanka::LoadAllBox() {

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
        boxes.hurtbox.head.offset[FighterState::Crouch]={{61,22}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{37,-23}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{44,-73}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{100,50},{100,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{38,91},{53,46}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{9,41},{28,-4}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{10,-9},{38,-54}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{100,50},{100,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{53,46},{38,91}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{28,-4},{9,41}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{38,-54},{10,-9}};
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
    }
}
