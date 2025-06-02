//
// Created by asus on 2025/2/27.
//

#include "Fighters/Dhalsim.hpp"
namespace Util {
    Dhalsim::Dhalsim(): Fighter("Dhalsim") {
        LoadFighterData();
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/india.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/india_dark.png");
        country_position={{-228, 97},0,{1,1}};
        face_postion={{161, -253},0,{1,1}};
        BackgroundInit(13);
        StateInit();
        LoadCommonVelocities();
        Dhalsim::LoadAnimations();
        Dhalsim::LoadOffsetVelocity();
        Dhalsim::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Dhalsim::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Dhalsim::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(6,"Idle");
        animations[FighterState::Backward] = ActionInit(7,"Backward");
        animations[FighterState::Forward] = ActionInit(7,"Forward");
        animations[FighterState::JumpUP] = ActionInit(5, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(5, "JumpForward");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(3, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;
        animations[FighterState::LP] = ActionInit(5, "LP");
        animations[FighterState::MP] = ActionInit(7, "MP");
        animations[FighterState::HP] = ActionInit(7, "HP");
        animations[FighterState::LK] = ActionInit(5, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(6, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::KnockDownL] = animations[FighterState::KnockDownM] = animations[FighterState::KnockDownH] =ActionInit(3, "KnockDown");
        animations[FighterState::GetUp] = ActionInit(3, "GetUp");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(2, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(7, "CrouchMP");
        animations[FighterState::CrouchHP] = animations[FighterState::CrouchMP];
        animations[FighterState::CrouchHK] = animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK] = ActionInit(2, "CrouchLK");

        animations[FighterState::JumpMP] =animations[FighterState::JumpLP] = animations[FighterState::JumpHP] =ActionInit(3, "JumpHP");
        animations[FighterState::JumpLK] = animations[FighterState::JumpMK] = animations[FighterState::JumpHK] = ActionInit(3, "JumpHK");

        animations[FighterState::JumpAttackEnd] = ActionInit(1, "JumpAttackEnd");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(2, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(6, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100,100,100,100,100,100};
        frames[FighterState::Forward]={100,100,100,100,100,100,100};
        frames[FighterState::Backward]={100,100,100,100,100,100,100};
        frames[FighterState::JumpUP]={90,120,150,120,90};
        frames[FighterState::JumpForward]={90,120,150,120,90};
        frames[FighterState::JumpBackward]=frames[FighterState::JumpForward];
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={40,40,40};
        frames[FighterState::CrouchUp]={40,40,40};
        frames[FighterState::LP]={60,60,90,60,60};
        frames[FighterState::MP]={90,90,120,120,150,210,120};
        frames[FighterState::HP]={90,120,180,210,240,180,150};
        frames[FighterState::LK]={90,120,150,120,120};
        frames[FighterState::MK]={120,120,180,210,150};
        frames[FighterState::HK]={90,120,120,150,180,180};

        frames[FighterState::CrouchLP]={150,180};
        frames[FighterState::CrouchMP]={90,120,120,180,150,120,90};
        frames[FighterState::CrouchHP]={90,120,180,210,240,180,150};
        frames[FighterState::CrouchLK]={180,270};
        frames[FighterState::CrouchMK]={180,300};
        frames[FighterState::CrouchHK]={180,330};

        frames[FighterState::JumpLP]={90,90,240};
        frames[FighterState::JumpMP]={90,120,360};
        frames[FighterState::JumpHP]={120,120,480};
        frames[FighterState::JumpLK]={90,90,240};
        frames[FighterState::JumpMK]={90,120,360};
        frames[FighterState::JumpHK]={120,120,480};
        frames[FighterState::JumpAttackEnd]={100};

        frames[FighterState::HurtHeadL] = {90,90};
        frames[FighterState::HurtHeadM] = {160,160};
        frames[FighterState::HurtHeadH] = {210,210};
        frames[FighterState::HurtBodyL] = {90,90};
        frames[FighterState::HurtBodyM] = {160,160};
        frames[FighterState::HurtBodyH] = {210,210};

        frames[FighterState::KnockDownL] = {120,120,150};
        frames[FighterState::KnockDownM] = {140,140,170};
        frames[FighterState::KnockDownH] = {180,180,220};
        frames[FighterState::GetUp] = {150,150,150};

        frames[FighterState::BackwardBlock] = {60,60};
        frames[FighterState::CrouchBlock] = {60,60};

        frames[FighterState::WinStart]={180};
        frames[FighterState::Win]={180,180};

        frames[FighterState::TimeOverLoss]={180,180,180,180,180,180};
        frames[FighterState::DefeatedLoss]={180,180,180};


    }
    void Dhalsim::LoadOffsetVelocity() {
        Initialvelocity.x[FighterState::CrouchLK] = 3;
        Initialvelocity.x[FighterState::CrouchMK] = 4;
        Initialvelocity.x[FighterState::CrouchHK] = 5;
        attacktype[FighterState::CrouchHK]=attacktype[FighterState::CrouchMK]=attacktype[FighterState::CrouchLK]=AttackType::Lower;
        offset[FighterState::Idle]={{-3,-1},{-11,2},{-10,-8},{-3,-16},{3,-17},{-1,-8}};
        offset[FighterState::Crouch]={{-7,-56}};
        offset[FighterState::CrouchDown]={{-8,-21},{-17,-39},{-7,-56}};
        offset[FighterState::CrouchUp]={{-7,-56},{-17,-39},{-8,-21}};
        //Stand attack offset
        offset[FighterState::LP]={{31,-25},{27,-29},{113,-33},{27,-30},{30,-24}};
        offset[FighterState::MP]={{-50,-5},{37,-38},{134,-85},{232,-85},{136,-85},{39,-38},{-52,-5}};
        offset[FighterState::HP]={{-52,-8},{39,-39},{136,-85},{278,-87},{137,-85},{38,-40},{-50,-7}};
        offset[FighterState::LK]={{24,-10},{129,14},{201,16},{130,15},{24,-12}};
        offset[FighterState::MK]={{21,-14},{147,-12},{243,20},{151,-10},{26,-15}};
        offset[FighterState::HK]={{49,-10},{74,5},{92,1},{163,0},{283,6},{111,-16}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{3,-56},{87,-58}};;
        offset[FighterState::CrouchMP]={{-45,-38},{27,-72},{103,-98},{200,-98},{102,-100},{25,-73},{-44,-40}};
        offset[FighterState::CrouchHP]=offset[FighterState::CrouchMP];
        offset[FighterState::CrouchLK]={{-30,-57},{-30,-77}};
        offset[FighterState::CrouchMK]=offset[FighterState::CrouchLK];
        offset[FighterState::CrouchHK]=offset[FighterState::CrouchLK];

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-14,-1},{-22,-4}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{2,-7},{10,-17}};

        offset[FighterState::KnockDownL]=offset[FighterState::KnockDownM]=offset[FighterState::KnockDownH]={{-93,-56},{-69,-116},{-63,-113}};
        offset[FighterState::GetUp]={{-129,-81},{-122,-45},{-74,3}};

        offset[FighterState::BackwardBlock]={{-28,-2},{-37,-7}};
        offset[FighterState::CrouchBlock]={{-5,-53},{-27,-51}};

        offset[FighterState::Win]={{104,5},{103,8}};
        offset[FighterState::WinStart]={{102,9}};

        offset[FighterState::TimeOverLoss]={{-12,-22},{-19,34},{-19,44},{-11,45},{3,47},{2,52}};
        offset[FighterState::DefeatedLoss]={{-87,-8},{-224,-68},{-138,-112}};

        offset[FighterState::JumpUP]={{-15,50},{-13,34},{-9,28},{-13,34},{-15,50}};
        offset[FighterState::JumpForward]={{-9,45},{-14,26},{-37,23},{-34,36},{-13,45}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
        offset[FighterState::JumpHP]=offset[FighterState::JumpMP]=offset[FighterState::JumpLP]={{-19,21},{66,25},{160,27}};
        offset[FighterState::JumpLK]=offset[FighterState::JumpMK]=offset[FighterState::JumpHK]={{-27,35},{-11,29},{74,15}};
        offset[FighterState::JumpAttackEnd]={{-22,20}};

    }
    void Dhalsim::LoadAllBox() {

        boxes.pushbox.size[FighterState::Idle]={100,200};
        boxes.pushbox.offset[FighterState::Idle]={-20,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={100,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={0,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{100,80},{100,80},{100,80},{100,80},{100,80},{100,80}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{100,140},{100,140},{100,140},{100,140},{100,140},{100,140}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{6,101},{8,101},{13,95},{16,90},{11,93},{8,99}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{-19,50},{-17,49},{-14,40},{-11,37},{-17,43},{-18,46}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-24,-60},{-19,-62},{-20,-69},{-20,-69},{-24,-66},{-23,-64}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{120,50}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{120,70}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{43,65}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{5,20}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{-12,-50}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{100,50},{100,50},{120,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{100,130},{100,100},{120,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{23,101},{37,75},{43,35}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{-8,52},{0,23},{5,-10}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-10,-50},{-9,-60},{-12,-80}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{100,50},{100,50},{100,50}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{100,50},{100,70},{100,100}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{43,35},{37,75},{23,101}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{5,-10},{0,23},{-8,52}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{-12,-80},{-9,-60},{-10,-50}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{120,60},{120,60}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{120,80},{120,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{9,79},{-35,79}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{-13,35},{-30,26}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{-3,-45},{-13,-43}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{-12,110},{-32,114}};
        boxes.hurtbox.body.offset[FighterState::BackwardBlock]={{-15,61},{-50,68}};
        boxes.hurtbox.leg.size[FighterState::BackwardBlock]={{100,140},{100,140}};
        boxes.hurtbox.leg.offset[FighterState::BackwardBlock]={{-11,-66},{-30,-58}};
        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{120,90},{140,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{44,71},{71,66}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-4,27},{14,32}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLP]={{-15,-36},{-1,-40}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]=boxes.hurtbox.head.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]=boxes.hurtbox.body.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchLK]={{120,80},{110,90}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]=boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchLK]={{130,80},{220,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]=boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchLK]={{26,72},{32,23}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]=boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchLK]={{1,33},{49,-24}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]=boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{3,-47},{216,-38}};

        boxes.hurtbox.head.size[FighterState::CrouchHP]=boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]=boxes.hurtbox.body.size[FighterState::CrouchMP]={{100,70},{100,70},{140,70},{200,70},{140,70},{100,70},{100,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]=boxes.hurtbox.leg.size[FighterState::CrouchMP]={{130,80},{130,80},{130,80},{130,80},{130,80},{130,80},{130,80}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]=boxes.hurtbox.head.offset[FighterState::CrouchMP]={{-4,84},{172,17},{194,-44},{194,-44},{194,-44},{170,16},{1,84}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]=boxes.hurtbox.body.offset[FighterState::CrouchMP]={{7,31},{116,-31},{169,-72},{213,-69},{169,-72},{116,-31},{7,31}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]=boxes.hurtbox.leg.offset[FighterState::CrouchMP]={{37,-63},{21,-64},{38,-69},{42,-65},{39,-68},{21,-64},{36,-69}};



        //hurtbox Stand Attack
        boxes.hurtbox.head.offset[FighterState::LP]={{52,105},{58,99},{57,87},{57,93},{49,106}};
        boxes.hurtbox.body.offset[FighterState::LP]={{16,65},{13,64},{27,50},{7,65},{14,64}};
        boxes.hurtbox.leg.size[FighterState::LP]={{150,130},{150,130},{150,130},{150,130},{150,130}};
        boxes.hurtbox.leg.offset[FighterState::LP]={{-4,-57},{6,-56},{6,-60},{6,-59},{0,-61}};

        boxes.hurtbox.head.offset[FighterState::MP]={{-5,121},{190,58},{254,-33},{256,-32},{256,-32},{193,57},{-5,123}};
        boxes.hurtbox.body.size[FighterState::MP]={{120,80},{120,60},{170,80},{190,80},{170,80},{120,60},{120,80}};
        boxes.hurtbox.body.offset[FighterState::MP]={{5,69},{129,23},{222,-63},{255,-65},{232,-64},{136,16},{5,68}};
        boxes.hurtbox.leg.size[FighterState::MP]={{130,160},{150,120},{150,120},{150,120},{150,120},{150,120},{130,160}};
        boxes.hurtbox.leg.offset[FighterState::MP]={{13,-58},{95,-77},{83,-81},{83,-81},{83,-81},{94,-77},{13,-63}};

        boxes.hurtbox.head.offset[FighterState::HP]={{-2,124},{194,58},{260,-32},{263,-36},{263,-37},{196,58},{2,123}};
        boxes.hurtbox.body.size[FighterState::HP]={{120,80},{120,60},{170,80},{210,80},{170,80},{120,60},{120,80}};
        boxes.hurtbox.body.offset[FighterState::HP]={{8,69},{129,31},{219,-57},{281,-56},{220,-59},{139,22},{9,72}};
        boxes.hurtbox.leg.size[FighterState::HP]={{130,160},{150,120},{150,120},{150,120},{150,120},{150,120},{130,160}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{24,-64},{96,-80},{117,-79},{117,-79},{117,-79},{90,-76},{17,-64}};

        boxes.hurtbox.head.offset[FighterState::LK]={{62,115},{39,162},{40,162},{40,162},{64,111}};
        boxes.hurtbox.body.size[FighterState::LK]={{100,80},{100,80},{100,80},{100,80},{100,80}};
        boxes.hurtbox.body.offset[FighterState::LK]={{-16,84},{22,114},{19,113},{19,113},{-19,83}};
        boxes.hurtbox.leg.size[FighterState::LK]={{100,160},{80,180},{80,180},{80,180},{100,160}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{-17,-47},{32,-47},{31,-46},{31,-46},{-17,-47}};

        boxes.hurtbox.head.offset[FighterState::MK]={{65,112},{90,119},{90,121},{90,121},{70,110}};
        boxes.hurtbox.body.size[FighterState::MK]={{100,80},{120,80},{120,70},{120,70},{110,80},{110,80}};
        boxes.hurtbox.body.offset[FighterState::MK]={{-12,88},{69,93},{71,91},{70,95},{-18,79}};
        boxes.hurtbox.leg.size[FighterState::MK]={{100,140},{80,180},{80,180},{80,180},{100,140}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{-18,-53},{36,-38},{36,-38},{36,-38},{-17,-55}};

        boxes.hurtbox.head.offset[FighterState::HK]={{-2,118},{18,122},{29,125},{52,128},{50,126},{54,116}};
        boxes.hurtbox.body.size[FighterState::HK]={{90,80},{80,70},{90,70},{110,70},{120,80},{120,80}};
        boxes.hurtbox.body.offset[FighterState::HK]={{21,83},{16,85},{18,94},{20,94},{22,89},{33,79}};
        boxes.hurtbox.leg.size[FighterState::HK]={{110,160},{80,180},{80,180},{80,180},{80,180},{110,160}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{-3,-42},{9,-39},{20,-48},{22,-43},{19,-43},{32,-42}};

        boxes.hurtbox.head.offset[FighterState::JumpUP]={{-22,137},{10,92},{19,58},{10,92},{-22,137}};
        boxes.hurtbox.body.offset[FighterState::JumpUP]={{-4,78},{-29,40},{-14,7},{-29,40},{-4,78}};
        boxes.hurtbox.leg.size[FighterState::JumpUP]={{130,160},{140,120},{150,100},{160,90},{150,100}};
        boxes.hurtbox.leg.offset[FighterState::JumpUP]={{-11,-50},{-11,-58},{4,-72},{-11,-58},{-11,-50}};

        boxes.hurtbox.leg.size[FighterState::JumpForward]={{110,160},{100,140},{120,120},{120,140},{110,160}};
        boxes.hurtbox.body.size[FighterState::JumpForward]= {{100,80},{100,80},{120,80},{100,80},{100,80}};
        boxes.hurtbox.head.offset[FighterState::JumpForward]={{-23,145},{54,91},{-67,-101},{-137,43},{-27,147}};
        boxes.hurtbox.body.offset[FighterState::JumpForward]={{-16,92},{-10,69},{-30,-53},{-67,28},{-22,93}};
        boxes.hurtbox.leg.offset[FighterState::JumpForward]={{-16,-37},{-29,-37},{-27,1},{45,-27},{-15,-34}};

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

        boxes.hurtbox.head.size[FighterState::JumpMP]=boxes.hurtbox.head.size[FighterState::JumpLP]=boxes.hurtbox.head.size[FighterState::JumpHP]= {{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::JumpMP]=boxes.hurtbox.body.size[FighterState::JumpLP]=boxes.hurtbox.body.size[FighterState::JumpHP]= {{100,80},{130,80},{140,80}};
        boxes.hurtbox.leg.size[FighterState::JumpMP]=boxes.hurtbox.leg.size[FighterState::JumpLP]=boxes.hurtbox.leg.size[FighterState::JumpHP]={{100,140},{120,140},{120,140}};
        boxes.hurtbox.head.offset[FighterState::JumpMP]=boxes.hurtbox.head.offset[FighterState::JumpLP]=boxes.hurtbox.head.offset[FighterState::JumpHP]={{16,109},{89,78},{89,97}};
        boxes.hurtbox.body.offset[FighterState::JumpMP]=boxes.hurtbox.body.offset[FighterState::JumpLP]=boxes.hurtbox.body.offset[FighterState::JumpHP]={{-17,58},{36,38},{31,57}};
        boxes.hurtbox.leg.offset[FighterState::JumpMP]=boxes.hurtbox.leg.offset[FighterState::JumpLP]=boxes.hurtbox.leg.offset[FighterState::JumpHP]={{-3,-44},{18,-36},{22,-24}};

        boxes.hurtbox.head.size[FighterState::JumpMK]=boxes.hurtbox.head.size[FighterState::JumpLK]=boxes.hurtbox.head.size[FighterState::JumpHK]= {{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::JumpMK]=boxes.hurtbox.body.size[FighterState::JumpLK]=boxes.hurtbox.body.size[FighterState::JumpHK]= {{100,80},{100,80},{100,80}};
        boxes.hurtbox.leg.size[FighterState::JumpMK]=boxes.hurtbox.leg.size[FighterState::JumpLK]=boxes.hurtbox.leg.size[FighterState::JumpHK]={{130,140},{180,100},{190,100}};
        boxes.hurtbox.head.offset[FighterState::JumpMK]=boxes.hurtbox.head.offset[FighterState::JumpLK]=boxes.hurtbox.head.offset[FighterState::JumpHK]={{51,96},{-39,44},{-59,45}};
        boxes.hurtbox.body.offset[FighterState::JumpMK]=boxes.hurtbox.body.offset[FighterState::JumpLK]=boxes.hurtbox.body.offset[FighterState::JumpHK]={{-2,63},{-81,17},{-102,17}};
        boxes.hurtbox.leg.offset[FighterState::JumpMK]=boxes.hurtbox.leg.offset[FighterState::JumpLK]=boxes.hurtbox.leg.offset[FighterState::JumpHK]={{-1,-34},{-30,-63},{-48,-63}};

        boxes.hurtbox.leg.size[FighterState::JumpAttackEnd]={{150,160}};
        boxes.hurtbox.head.offset[FighterState::JumpAttackEnd]={{40,181}};
        boxes.hurtbox.body.offset[FighterState::JumpAttackEnd]={{22,123}};
        boxes.hurtbox.leg.offset[FighterState::JumpAttackEnd]={{-20,-5}};
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={176,50};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{170,74}};
        boxes.hitbox.size[FighterState::CrouchHP]=boxes.hitbox.size[FighterState::CrouchMP]={410,40};
        boxes.hitbox.offset[FighterState::CrouchHP]=boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{-1,-1},{338,-43},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHK]=boxes.hitbox.size[FighterState::CrouchMK]=boxes.hitbox.size[FighterState::CrouchLK]={290,90};
        boxes.hitbox.offset[FighterState::CrouchHK]=boxes.hitbox.offset[FighterState::CrouchMK]=boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{95,-32}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={190,50};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{-1,-1},{185,78},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={420,50};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{-1,-1},{390,-34},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={510,80};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{-1,-1},{430,-52},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={300,80};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{275,130},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MK]={300,80};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{337,162},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={380,90};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{320,130},{-1,-1}};

        //hitbox Jump Attack

        boxes.hitbox.size[FighterState::JumpHP]=boxes.hitbox.size[FighterState::JumpMP]=boxes.hitbox.size[FighterState::JumpLP]={350,160};
        boxes.hitbox.offset[FighterState::JumpHP]=boxes.hitbox.offset[FighterState::JumpMP]=boxes.hitbox.offset[FighterState::JumpLP]={{-1,-1},{-1,-1},{244,-23}};
        boxes.hitbox.size[FighterState::JumpMK]=boxes.hitbox.size[FighterState::JumpLK]=boxes.hitbox.size[FighterState::JumpHK]={460,100};
        boxes.hitbox.offset[FighterState::JumpMK]=boxes.hitbox.offset[FighterState::JumpLK]=boxes.hitbox.offset[FighterState::JumpHK]={{-1,-1},{-1,-1},{140,-94}};
    }
    void Dhalsim::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(6, "Special_1");
        offset[FighterState::Special_1]={{-6,-10},{-48,-9},{-76,1},{1,2},{30,-6},{50,-6}};

        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LP]={90,90,90,90,120,300};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::MP]={90,90,90,90,150,360};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::HP]={90,90,90,90,180,420};

        boxes.hurtbox.body.size[FighterState::Special_1]={{100,80},{100,80},{120,100},{100,100},{120,100},{120,80}};
        boxes.hurtbox.leg.size[FighterState::Special_1]={{100,150},{100,140},{100,160},{100,160},{100,160},{100,150}};

        boxes.hurtbox.head.offset[FighterState::Special_1]={{-22,120},{-97,125},{-155,135},{68,132},{137,81},{170,35}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{-41,56},{-70,56},{-101,85},{1,91},{46,83},{85,50}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{-21,-59},{-25,-59},{-34,-46},{14,-43},{20,-50},{38,-60}};

        StateEnter[FighterState::Special_1]=[this] { YogaFireStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { YogaFireStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Dhalsim/SP1.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={
            SpecialMoveDirection::Forward,
            SpecialMoveDirection::Forward_down,
            SpecialMoveDirection::down
        };
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ANY_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Command;

        animations[FighterState::Special_2]=ActionInit(19, "Special_2");
        offset[FighterState::Special_2]={{-7,-6},{-48,-8},{-75,1},{1,8},{32,-1},{56,-5},{119,-11},{129,-11},{149,-13},{159,-12},{164,-12},{173,-13},{170,
-14},{173,-9},{167,-13},{158,-14},{150,-13},{138,-13},{134,-14}};

        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LP]={60,90,120,60,60,60,60,60,60,60,60,60,60,60,60,60,240,180,120};

        boxes.hurtbox.body.size[FighterState::Special_2]={{100,100},{100,100},{120,120},{100,120},{120,120},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80},{140,80}};
        boxes.hurtbox.leg.size[FighterState::Special_2]={{100,140},{100,140},{100,150},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140},{100,140}};

        boxes.hurtbox.head.offset[FighterState::Special_2]={{-20,116},{-95,122},{-150,134},{70,134},{142,85},{172,34},{173,34},{171,30},{169,26},{173,28},{167,26},{169,26},{169,26},{172,27},{172,27},{169,26},{174,27},{171,26},{171,26}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{-43,59},{-61,55},{-88,81},{-6,93},{35,79},{78,53},{77,49},{76,49},{76,49},{76,49},{76,49},{74,49},{71,47},{75,48},{72,48},{73,47},{78,50},{73,47},{74,48}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{-22,-57},{-23,-61},{-31,-46},{16,-36},{24,-46},{39,-54},{40,-63},{40,-64},{38,-64},{38,-64},{36,-64},{39,-62},{39,-62},{39,-62},{38,-62},{38,-62},{39,-62},{40,-62},{40,-62}};

        boxes.hitbox.size[FighterState::Special_2]={280,200};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{300,22},{300,27},{300,27},{300,28},{300,28},{300,33},{300,31},{300,30},{-1,-1},{-1,-1},{-1,-1},};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LP]=15;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LP]=HitStrength::SP;

        StateEnter[FighterState::Special_2]=[this] { YogaFlameStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { YogaFlameStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Dhalsim/SP2.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_2].command={};
        SpecialMoveData.SkillCommand[FighterState::Special_2].requiredAttack=AttackButton::ALL_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_2].commandtype=CommandType::Null;

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Dhalsim/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Dhalsim/Loss.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_1].SpecialNumer=SpecialNumer::Special_1;
        SpecialMoveData.SkillCommand[FighterState::Special_2].SpecialNumer=SpecialNumer::Special_2;
    }
    void Dhalsim::YogaFireStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Dhalsim::YogaFireStateUpdate() {
        if (ActionNow->GetCurrentFrameIndex()==5){AddFlyingObject(FlyingObjectType::YogaFire,ButtonType);ClearButtonType();}
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Dhalsim::YogaFlameStateEnter() {
        controller->ClearAiSpecial();
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Dhalsim::YogaFlameStateUpdate() {
        if (HitEnemy&&ActionNow->GetCurrentFrameIndex()<=15){ActionNow->SetCurrentFrame(16);}
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
}