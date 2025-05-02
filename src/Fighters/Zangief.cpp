//
// Created by asus on 2025/2/27.
//

#include "Fighters/Zangief.hpp"
namespace Util {
    Zangief::Zangief(): Fighter("Zangief") {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Zangief/Zangief_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Zangief/Zangief_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/ussr.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/ZangiefTheme.mp3");
        country_position={{-244, 220},0,{1,1}};
        BackgroundInit(8);
        StateInit();
        LoadCommonVelocities();
        Zangief::LoadAnimations();
        Zangief::LoadOffsetVelocity();
        Zangief::LoadAllBox();
        Zangief::LoadAttackSound();
        Fighter::LoadAttackAndType();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Zangief::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(4,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::JumpUP] = ActionInit(7, "JumpUP");
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

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(2, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(3, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(5, "CrouchHP");
        animations[FighterState::CrouchLK] = animations[FighterState::CrouchMP];
        animations[FighterState::CrouchMK] = animations[FighterState::CrouchHP];
        animations[FighterState::CrouchHK] = animations[FighterState::CrouchHP];

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(2, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(3, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100, 150, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,60,60,60,60,60,60};
        frames[FighterState::JumpForward]=frames[FighterState::JumpUP];
        frames[FighterState::JumpBackward]=frames[FighterState::JumpUP];
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={120,60,60};
        frames[FighterState::CrouchUp]={60,60,120};
        frames[FighterState::LP]={60,60,60};
        frames[FighterState::MP]={60,60,60,60};
        frames[FighterState::HP]={60,60,60,60,60,60,60};
        frames[FighterState::LK]={60,60,60};
        frames[FighterState::MK]={60,60,60,60,60};
        frames[FighterState::HK]={60,60,60};

        frames[FighterState::CrouchLP]={60,60};
        frames[FighterState::CrouchMP]={60,60,60};
        frames[FighterState::CrouchHP]={60,60,60,60,60};
        frames[FighterState::CrouchLK]=frames[FighterState::CrouchMP];
        frames[FighterState::CrouchMK]=frames[FighterState::CrouchHP];
        frames[FighterState::CrouchHK]=frames[FighterState::CrouchHP];

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150};
        frames[FighterState::CrouchBlock] = {150,150};

        frames[FighterState::WinStart]={180};
        frames[FighterState::Win]={180, 180};

        frames[FighterState::TimeOverLoss]={180,180,180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Zangief::LoadOffsetVelocity() {
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
        offset[FighterState::CrouchMP]={{-6,-33},{66,-27},{-9,-33}};
        offset[FighterState::CrouchHP]={{-47,-36},{-30,-43},{16,-38},{-36,-41},{-48,-38}};
        offset[FighterState::CrouchLK]=offset[FighterState::CrouchMP];
        offset[FighterState::CrouchMK]=offset[FighterState::CrouchHP];
        offset[FighterState::CrouchHK]=offset[FighterState::CrouchHP];

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::BackwardBlock]={{-1,4},{-31,-2}};
        offset[FighterState::CrouchBlock]={{-33,-45},{-54,-58}};

        offset[FighterState::Win]={{4,10},{6,67}};
        offset[FighterState::WinStart]={{6,5}};

        offset[FighterState::TimeOverLoss]={{8,2},{5,2},{8,1}};
        offset[FighterState::DefeatedLoss]={{-103,19},{-323,-77},{-334,-105}};
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

        boxes.hurtbox.head.size[FighterState::CrouchLK]=boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]=boxes.hurtbox.body.size[FighterState::CrouchMP]={{140,70},{140,60},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]=boxes.hurtbox.leg.size[FighterState::CrouchMP]={{180,100},{200,100},{180,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]=boxes.hurtbox.head.offset[FighterState::CrouchMP]={{-2,88},{3,73},{-7,91}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]=boxes.hurtbox.body.offset[FighterState::CrouchMP]={{-25,35},{-9,25},{-29,34}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]=boxes.hurtbox.leg.offset[FighterState::CrouchMP]={{-6,-42},{15,-60},{-7,-46}};

        boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchHK]=boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchHK]=boxes.hurtbox.body.size[FighterState::CrouchHP]={{140,70},{100,100},{120,100},{100,100},{140,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchHK]=boxes.hurtbox.leg.size[FighterState::CrouchHP]={{180,110},{170,100},{150,100},{170,100},{180,110}};
        boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchHK]=boxes.hurtbox.head.offset[FighterState::CrouchHP]={{11,95},{67,84},{92,100},{61,86},{9,93}};
        boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchHK]=boxes.hurtbox.body.offset[FighterState::CrouchHP]={{0,39},{26,33},{77,58},{26,33},{0,39}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchHK]=boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{17,-54},{24,-57},{29,-43},{24,-57},{17,-54}};
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