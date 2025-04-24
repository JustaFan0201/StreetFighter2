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
        LoadCommonVelocities();
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

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(4, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(4, "HurtBody");

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

        offset[FighterState::BackwardBlock]={{-9,-8},{-20,-13}};
        offset[FighterState::CrouchBlock]={{-14,-65},{-19,-65}};
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
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={160,40};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{216,4},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMP]={150,70};
        boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{310,75},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]={140,70};
        boxes.hitbox.offset[FighterState::CrouchHP]={{-1,-1},{-1,-1},{305,125},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
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
    }
}
