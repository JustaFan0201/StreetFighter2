//
// Created by asus on 2025/2/27.
//

#include "Fighters/Guile.hpp"
namespace Util {
    Guile::Guile():Fighter("Guile"){
        winword=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/WinWord.png");
        lossface=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_LossFace.png");
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/usa_dark.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/GuileTheme.mp3");
        country_position={{350, 140},0,{1,1}};
        face_postion={{161, -150},0,{1,1}};
        BackgroundInit(5);
        StateInit();
        LoadCommonVelocities();
        Guile::LoadAnimations();
        Guile::LoadOffsetVelocity();
        Guile::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Guile::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Guile::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(6,"Idle");
        animations[FighterState::Backward] = ActionInit(5,"Backward");
        animations[FighterState::Forward] = ActionInit(5,"Forward");
        animations[FighterState::JumpUP] = ActionInit(8, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(7, "JumpForward");
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

        animations[FighterState::JumpMP] = animations[FighterState::JumpLP] = ActionInit(3, "JumpLP");
        animations[FighterState::JumpHP] = ActionInit(3, "JumpHP");
        animations[FighterState::JumpLK] = ActionInit(3, "JumpLK");
        animations[FighterState::JumpMK] = ActionInit(4, "JumpMK");
        animations[FighterState::JumpHK] = ActionInit(5, "JumpHK");
        animations[FighterState::JumpAttackEnd] = ActionInit(1, "JumpAttackEnd");

        animations[FighterState::WinStart]=ActionInit(2, "WinStart");
        animations[FighterState::Win]=ActionInit(1, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(2, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100, 100, 100, 100, 100, 100};
        frames[FighterState::Forward]={120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,90,120,120,120,120,90,60};
        frames[FighterState::JumpForward]={60,90,120,150,120,90,60};
        frames[FighterState::JumpBackward]={60,90,120,150,120,90,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60,60};
        frames[FighterState::CrouchUp]={60,60,60};
        frames[FighterState::LP]={70,90,70};
        frames[FighterState::MP]={70,80,90,80,80};
        frames[FighterState::HP]={80,80,110,100,100};
        frames[FighterState::LK]={80,80,90};
        frames[FighterState::MK]={80,80,90,90,90,90};
        frames[FighterState::HK]={70,70,90,100,100,100};

        frames[FighterState::CrouchLP]={80,90,80};
        frames[FighterState::CrouchMP]={70,90,90,70};
        frames[FighterState::CrouchHP]={80,80,110,130,90};
        frames[FighterState::CrouchLK]={80,90,90};
        frames[FighterState::CrouchMK]={70,70,70,70,70};
        frames[FighterState::CrouchHK]={70,70,70,70,70,70,70,70,70,70,70};

        frames[FighterState::JumpLP]={150,150,150};
        frames[FighterState::JumpMP]={140,140,180};
        frames[FighterState::JumpHP]={120,160,160};
        frames[FighterState::JumpLK]={120,120,200};
        frames[FighterState::JumpMK]={120,120,120,180};
        frames[FighterState::JumpHK]={100,140,200,140,100};
        frames[FighterState::JumpAttackEnd]={80};

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150,150};
        frames[FighterState::CrouchBlock] = {150,150};

        frames[FighterState::WinStart]={200, 200};
        frames[FighterState::Win]={200};

        frames[FighterState::TimeOverLoss]={180, 180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Guile::LoadOffsetVelocity() {
        attacktype[FighterState::CrouchHK]=attacktype[FighterState::CrouchMK]=attacktype[FighterState::CrouchLK]=AttackType::Lower;
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
        offset[FighterState::CrouchLP]={{20,-43},{64,-43},{52,-45}};
        offset[FighterState::CrouchMP]={{34,-48},{55,-51},{39,-50},{31,-48}};
        offset[FighterState::CrouchHP]={{2,-30},{17,-19},{25,6},{5,62},{25,8}};
        offset[FighterState::CrouchLK]={{24,-47},{24,-47},{93,-57}};
        offset[FighterState::CrouchMK]={{-87,-58},{-51,-42},{24,-59},{-42,-42},{-37,-42}};
        offset[FighterState::CrouchHK]={{19,-42},{105,-51},{163,-50},{130,-51},{86,-47},{55,-49},{55,-63},{88,-43},{160,-60},{94,-40},{87,-40}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::BackwardBlock]={{-8,-4},{-9,-23},{11,-8}};
        offset[FighterState::CrouchBlock]={{-18,-32},{-24,-30}};

        offset[FighterState::Win]={{-23,14}};
        offset[FighterState::WinStart]={{-27,33},{-32,24}};

        offset[FighterState::TimeOverLoss]={{24,33},{24,33}};
        offset[FighterState::DefeatedLoss]={{-73,7},{-153,-46},{-262,-103}};

        offset[FighterState::JumpUP]={{-42,50},{-63,41},{-73,36},{-53,10},{-55,6},{-69,18},{-63,48},{-44,52}};
        offset[FighterState::JumpForward]={{-18,46},{-36,-21},{-48,-4},{-46,19},{-73,-2},{-55,12},{-83,50}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
        offset[FighterState::JumpMP]=offset[FighterState::JumpLP]={{-32,53},{-39,25},{0,15}};
        offset[FighterState::JumpHP]={{-62,39},{1,52},{3,19}};
        offset[FighterState::JumpMK]={{0,44},{-31,36},{-26,35}};
        offset[FighterState::JumpHK]={{-47,3},{-55,5},{-34,3},{-17,-1}};
        offset[FighterState::JumpAttackEnd]={{-4,-1}};

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

        boxes.hurtbox.head.offset[FighterState::JumpUP]={{33,130},{13,92},{-3,68},{22,25},{22,25},{-3,68},{13,92},{33,130}};
        boxes.hurtbox.body.offset[FighterState::JumpUP]={{-1,85},{-24,50},{-28,28},{-5,-9},{-5,-9},{-28,28},{-24,50},{-1,85}};
        boxes.hurtbox.leg.size[FighterState::JumpUP]={{160,180},{180,125},{180,80},{180,90},{180,90},{180,80},{180,125},{160,180}};
        boxes.hurtbox.leg.offset[FighterState::JumpUP]={{2,-31},{-19,-43},{-28,-48},{-17,-73},{-17,-73},{-28,-48},{-19,-43},{2,-31}};

        boxes.hurtbox.body.size[FighterState::JumpForward]={{150,100},{130,100},{140,100},{160,80},{150,100},{150,100},{130,100}};
        boxes.hurtbox.leg.size[FighterState::JumpForward]={{160,170},{160,110},{200,110},{200,110},{190,110},{200,125},{160,170}};
        boxes.hurtbox.head.offset[FighterState::JumpForward]={{71,99},{80,-58},{9,-94},{-54,-100},{-126,-91},{-115,7},{-146,105}};
        boxes.hurtbox.body.offset[FighterState::JumpForward]={{33,65},{19,-62},{4,-54},{-31,-57},{-78,-56},{-51,-13},{-89,68}};
        boxes.hurtbox.leg.offset[FighterState::JumpForward]={{-51,-36},{-87,-45},{-71,-14},{-39,9},{-4,-24},{-7,-63},{-27,-23}};

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

        boxes.hurtbox.body.size[FighterState::JumpMP]=boxes.hurtbox.body.size[FighterState::JumpLP]={{150,90},{130,80},{130,100},{130,100},{130,100}};
        boxes.hurtbox.leg.size[FighterState::JumpMP]=boxes.hurtbox.leg.size[FighterState::JumpLP]={{180,160},{180,130},{180,110},{200,110},{200,110}};
        boxes.hurtbox.head.offset[FighterState::JumpMP]=boxes.hurtbox.head.offset[FighterState::JumpLP]={{12,139},{38,59},{55,27}};
        boxes.hurtbox.body.offset[FighterState::JumpMP]=boxes.hurtbox.body.offset[FighterState::JumpLP]={{-8,89},{-9,26},{-10,11}};
        boxes.hurtbox.leg.offset[FighterState::JumpMP]=boxes.hurtbox.leg.offset[FighterState::JumpLP]={{-6,-33},{-24,-46},{-38,-68}};

        boxes.hurtbox.body.size[FighterState::JumpHP]={{135,100},{140,100},{150,100},{150,100}};
        boxes.hurtbox.leg.size[FighterState::JumpHP]={{130,140},{180,110},{170,140},{210,110}};
        boxes.hurtbox.head.offset[FighterState::JumpHP]={{-22,88},{137,63},{20,63}};
        boxes.hurtbox.body.offset[FighterState::JumpHP]={{15,62},{125,2},{4,23}};
        boxes.hurtbox.leg.offset[FighterState::JumpHP]={{70,-37},{42,-82},{17,-55}};

        boxes.hurtbox.body.size[FighterState::JumpLK]={{160,80},{160,90},{140,100}};
        boxes.hurtbox.leg.size[FighterState::JumpLK]={{150,140},{140,140},{110,120}};
        boxes.hurtbox.head.offset[FighterState::JumpLK]={{9,103},{11,102},{-7,81}};
        boxes.hurtbox.body.offset[FighterState::JumpLK]={{-13,49},{-5,54},{-6,35}};
        boxes.hurtbox.leg.offset[FighterState::JumpLK]={{-36,-46},{-18,-39},{-56,-62}};

        boxes.hurtbox.body.size[FighterState::JumpMK]={{180,80},{150,100},{150,100},{150,100}};
        boxes.hurtbox.leg.size[FighterState::JumpMK]={{170,110},{160,115},{210,100},{220,100}};
        boxes.hurtbox.head.offset[FighterState::JumpMK]={{-25,62},{-53,43},{-94,42},{-114,15}};
        boxes.hurtbox.body.offset[FighterState::JumpMK]={{-4,17},{-45,14},{-44,12},{-65,-17}};
        boxes.hurtbox.leg.offset[FighterState::JumpMK]={{15,-42},{-18,-40},{-25,-54},{-39,-88}};

        boxes.hurtbox.body.size[FighterState::JumpHK]={{110,90},{120,90},{130,100},{130,90},{130,19}};
        boxes.hurtbox.leg.size[FighterState::JumpHK]={{140,110},{220,110},{220,110},{220,110},{200,110}};
        boxes.hurtbox.head.offset[FighterState::JumpHK]={{-38,59},{-79,68},{-128,59},{-50,54},{-1,59}};
        boxes.hurtbox.body.offset[FighterState::JumpHK]={{1,25},{-49,19},{-75,22},{-17,15},{10,21}};
        boxes.hurtbox.leg.offset[FighterState::JumpHK]={{20,-37},{-15,-47},{-38,-50},{16,-45},{41,-32}};

        boxes.hurtbox.head.offset[FighterState::JumpAttackEnd]={{9,102}};
        boxes.hurtbox.body.offset[FighterState::JumpAttackEnd]={{-12,52}};
        boxes.hurtbox.leg.offset[FighterState::JumpAttackEnd]={{-30,-44}};
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
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{45,139},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={240,50};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{-1,-1},{285,85},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={200,70};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{170,-24}};
        boxes.hitbox.size[FighterState::MK]={200,60};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{245,-30},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={140,80};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{-1,-1},{200,115},{-1,-1},{-1,-1},{-1,-1}};

        //hitbox Jump Attack
        boxes.hitbox.size[FighterState::JumpMP]=boxes.hitbox.size[FighterState::JumpLP]={150,120};
        boxes.hitbox.offset[FighterState::JumpMP]=boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{-1,-1},{84,-52}};
        boxes.hitbox.size[FighterState::JumpHP]={195,60};
        boxes.hitbox.offset[FighterState::JumpHP]={{-1,-1},{-1,-1},{130,11}};
        boxes.hitbox.size[FighterState::JumpLK]={160,190};
        boxes.hitbox.offset[FighterState::JumpLK]={{-1,-1},{-1,-1},{59,44}};
        boxes.hitbox.size[FighterState::JumpMK]={285,80};
            boxes.hitbox.offset[FighterState::JumpMK]={{-1,-1},{-1,-1},{-1,-1},{39,-90}};
        boxes.hitbox.size[FighterState::JumpHK]={260,70};
        boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{-1,-1},{90,-24},{-1,-1},{-1,-1}};
    }
    void Guile::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(4, "Special_1");
        offset[FighterState::Special_1]={{-1,-14},{-47,-4},{4,-12},{89,-6}};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LP]={60,90,60,60};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::MP]={60,120,90,60};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::HP]={90,150,120,90};

        boxes.hurtbox.head.offset[FighterState::Special_1]={{38,90},{74,75},{76,76},{76,76}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{13,45},{20,44},{15,47},{7,50}};

        StateEnter[FighterState::Special_1]=[this] { SonicBoomStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { SonicBoomStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/SP1_L.wav");
        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::MP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/SP1_H.wav");
        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::HP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/SP1_H.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={
            SpecialMoveDirection::Forward,
            SpecialMoveDirection::Backward
        };
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ANY_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Pressed;
        SpecialMoveData.SkillCommand[FighterState::Special_1].chargetime[Keys::LP]=250;
        SpecialMoveData.SkillCommand[FighterState::Special_1].chargetime[Keys::MP]=500;
        SpecialMoveData.SkillCommand[FighterState::Special_1].chargetime[Keys::HP]=750;

        animations[FighterState::Special_2]=ActionInit(10, "Special_2");
        offset[FighterState::Special_2]={{9,-37},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::LK]={3,7};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::MK]={4,9};
        SpecialMoveData.animationData[FighterState::Special_2].initialvelocitys[Keys::HK]={5,11};

        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LK]={30,30,30,60,60,90,120,90,90,60};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::MP]={30,30,30,60,90,120,180,120,120,90};
        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::HP]={30,30,30,90,90,120,240,180,180,120};

        boxes.hurtbox.body.size[FighterState::Special_2]={{100,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::Special_2]={{120,85},{100,80},{100,85},{100,125},{100,125},{100,125},{100,125},{100,125},{100,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::Special_2]={{33,69},{9,143},{26,110},{-24,131},{-97,71},{-74,3},{-141,-55},{67,22},{32,86},{9,141}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{19,26},{-17,90},{-12,64},{-36,69},{0,72},{-3,60},{-66,-41},{29,62},{-21,64},{-23,85}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{30,-46},{-19,1},{-9,-2},{15,-6},{90,1},{103,65},{-13,56},{-31,31},{-18,-1},{-19,-16}};

        boxes.hitbox.size[FighterState::Special_2]={200,300};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{131,43},{-1,-1},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LK]=10;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::MK]=15;
        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::HK]=22;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LK]=HitStrength::L;
        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::MK]=HitStrength::M;
        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::HK]=HitStrength::H;

        StateEnter[FighterState::Special_2]=[this] { SommersaultStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { SommersaultStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/SP2_L.wav");
        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::MK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/SP2_L.wav");
        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::HK]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/SP2_H.wav");
        SpecialMoveData.SkillCommand[FighterState::Special_2].command={
            SpecialMoveDirection::Up,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_2].requiredAttack=AttackButton::ANY_KICK;
        SpecialMoveData.SkillCommand[FighterState::Special_2].commandtype=CommandType::Pressed;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::LK]=250;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::MK]=500;
        SpecialMoveData.SkillCommand[FighterState::Special_2].chargetime[Keys::HK]=750;
        SpecificStates.borderCheckStates.insert(FighterState::Special_2);

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Guile/Loss.wav");
    }
    void Guile::SonicBoomStateEnter() {
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::punch);
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Guile::SonicBoomStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex()==3){AddFlyingObject(FlyingObjectType::SonicBoom,ButtonType);ClearButtonType();}
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Guile::SommersaultStateEnter() {
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::kick);
        LoadCurrentSpecialMove(ButtonType);
        velocity=GetInitialvelocity();
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Guile::SommersaultStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex() <= 7) {
            velocity.x += velocity.x * 0.1f * Time::GetDeltaTimeMs() / 1000.0f;
            velocity.y += velocity.y * 0.05f * Time::GetDeltaTimeMs() / 1000.0f;
        } else {
            velocity.y += Gravity * Time::GetDeltaTimeMs() / 1000.0f;
        }
        if (GetAnimationIsEnd()&&GetCharacterIsOnFloor()) {ChangeState(FighterState::Idle);}
    }
}