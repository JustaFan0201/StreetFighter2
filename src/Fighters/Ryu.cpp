//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ryu.hpp"
namespace Util {
    Ryu::Ryu(): Fighter("Ryu",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ryu/Ryu_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ryu/Ryu_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/japan.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/RyuTheme.mp3");
        country_position={{14,90},0,{1,1}};
        BackgroundInit(15);
        StateInit();
        Ryu::LoadAnimations();
        Ryu::LoadOffsetVelocity();
        Ryu::LoadAllBox();
        Ryu::LoadAttackSound();
        Fighter::LoadAttackAndType();
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
        animations[FighterState::Crouchdown] = ActionInit(3, "Crouchdown");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(5, "MP");
        animations[FighterState::HP] = ActionInit(6, "HP");
        animations[FighterState::LK] = ActionInit(4, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        frames[FighterState::Idle]={100, 150, 200, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120};
        frames[FighterState::JumpForward]={60,90,120,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,120,90,60};
        frames[FighterState::Crouchdown]={60,60,60};
        frames[FighterState::LP]={30,60,90};
        frames[FighterState::MP]={30,60,120,60,30};
        frames[FighterState::HP]={60,90,180,90,60,60};
        frames[FighterState::LK]={30,60,90,60};
        frames[FighterState::MK]={30,60,120,60,30};
        frames[FighterState::HK]={60,90,180,90,90};

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150};
        frames[FighterState::CrouchBlock] = {150,150};
    }
    void Ryu::LoadOffsetVelocity() {
        Gravity=-4800;
        Friction=800;
        Initialvelocity.x[FighterState::Forward]=400;
        Initialvelocity.x[FighterState::Backward]=-400;
        Initialvelocity.x[FighterState::JumpForward]=500;
        Initialvelocity.x[FighterState::JumpBackward]=-500;
        Initialvelocity.y[FighterState::JumpForward]=2100;
        Initialvelocity.y[FighterState::JumpBackward]=2100;
        Initialvelocity.y[FighterState::JumpUP]=2000;

        Initialvelocity.x[FighterState::HurtBodyL]=Initialvelocity.x[FighterState::HurtHeadL]=-300;
        Initialvelocity.x[FighterState::HurtBodyM]=Initialvelocity.x[FighterState::HurtHeadM]=-400;
        Initialvelocity.x[FighterState::HurtBodyH]=Initialvelocity.x[FighterState::HurtHeadH]=-500;

        Initialvelocity.x[FighterState::BackwardBlock]=Initialvelocity.x[FighterState::CrouchBlock]=-200;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0}};
        offset[FighterState::Crouchdown]={{10,-9},{31,-30},{35,-43}};
        offset[FighterState::LP]={{5,3},{44,2},{3,3}};
        offset[FighterState::MP]={{14,5},{-9,5},{56,5},{-10,6},{15,6}};
        offset[FighterState::HP]={{15,5},{23,5},{67,5},{40,34},{23,6},{15,5}};
        offset[FighterState::LK]={{15,6},{64,4},{140,4},{64,5}};
        offset[FighterState::MK]={{20,12},{-25,10},{-25,10},{-27,9},{23,11}};
        offset[FighterState::HK]={{32,5},{45,12},{68,11},{44,-11},{3,-9}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::BackwardBlock]={{-3,3},{1,5}};
        offset[FighterState::CrouchBlock]={{35,-44},{16,-38}};
    }
    void Ryu::LoadAllBox() {
        borderCheckStates = {
            FighterState::Idle, FighterState::Forward, FighterState::Backward,
            FighterState::JumpUP, FighterState::JumpForward, FighterState::JumpBackward,
            FighterState::Crouchdown,
            FighterState::HurtBodyL, FighterState::HurtBodyM, FighterState::HurtBodyH,
            FighterState::HurtHeadL, FighterState::HurtHeadM, FighterState::HurtHeadH,
            FighterState::BackwardBlock,FighterState::CrouchBlock
        };

        boxes.pushbox.size[FighterState::Idle]={100,200};
        boxes.pushbox.offset[FighterState::Idle]={15,0};
        boxes.pushbox.size[FighterState::Crouchdown]={100,120};
        boxes.pushbox.offset[FighterState::Crouchdown]={15,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={50,50};
        boxes.hurtbox.body.size[FighterState::Idle]={100,100};
        boxes.hurtbox.leg.size[FighterState::Idle]={100,125};
        boxes.hurtbox.head.offset[FighterState::Idle]={{23,113},{28,110},{27,109},{26,117},{25,116},{25,116}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-15,57},{-15,57},{-10,55},{-10,54},{-12,53},{-12,53}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-12,-53},{-12,-52},{-12,-52},{-12,-52},{-11,-48},{-11,-48}};

        boxes.hurtbox.head.size[FighterState::Crouchdown]=boxes.hurtbox.head.size[FighterState::CrouchBlock]={50,50};
        boxes.hurtbox.body.size[FighterState::Crouchdown]=boxes.hurtbox.body.size[FighterState::CrouchBlock]={100,50};
        boxes.hurtbox.leg.size[FighterState::Crouchdown]=boxes.hurtbox.leg.size[FighterState::CrouchBlock]={100,50};
        boxes.hurtbox.head.offset[FighterState::Crouchdown]={{38,91},{53,46},{61,22}};
        boxes.hurtbox.body.offset[FighterState::Crouchdown]={{9,41},{28,-4},{37,-23}};
        boxes.hurtbox.leg.offset[FighterState::Crouchdown]={{10,-9},{38,-54},{44,-73}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{11,67},{-32,74}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{4,10},{-25,27}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{11,-45},{-8,-44}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{-5,113},{-21,111}};

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
    void Ryu::LoadAttackSound() {
        soundeffect[FighterState::LP]=soundeffect[FighterState::LK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_38 - Light Attack.wav")};
        soundeffect[FighterState::MP]=soundeffect[FighterState::MK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_39 - Medium Attack.wav")};
        soundeffect[FighterState::HP]=soundeffect[FighterState::HK]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_40 - Hard Attack.wav")};
        soundeffect[FighterState::HurtBodyL]=soundeffect[FighterState::HurtHeadL]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_42 - Jab Hit.wav")};
        soundeffect[FighterState::HurtBodyM]=soundeffect[FighterState::HurtHeadM]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_43 - Strong Hit.wav")};
        soundeffect[FighterState::HurtBodyH]=soundeffect[FighterState::HurtHeadH]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_44 - Fierce Hit.wav")};
        soundeffect[FighterState::BackwardBlock]=soundeffect[FighterState::CrouchBlock]={std::make_shared<SFX>(RESOURCE_DIR"/voice/04 Moves & Hits/SFII_51 - Blocked.wav")};
    }
}