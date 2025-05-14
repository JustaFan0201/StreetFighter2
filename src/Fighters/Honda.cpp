//
// Created by asus on 2025/2/27.
//

#include "Fighters/Honda.hpp"
namespace Util {
    Honda::Honda():Fighter("Honda"){
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Honda/Honda_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Honda/Honda_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/japan.png");
        country_dark=std::string(RESOURCE_DIR"/ScenePicture/slect/japan_dark.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/HondaTheme.mp3");
        country_position={{28, 168},0,{1,1}};
        face_postion={{-53, -150},0,{1,1}};
        BackgroundInit(7);
        StateInit();
        LoadCommonVelocities();
        Honda::LoadAnimations();
        Honda::LoadOffsetVelocity();
        Honda::LoadAllBox();
        Fighter::LoadAttackSound();
        Fighter::LoadAttackAndType();
        Honda::LoadSpecialMove();
        ActionNow = std::make_shared<AnimationSpace>(animations[FighterState::Idle],true,120,true,4);
        debugInit();
    }
    void Honda::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(4,"Idle");
        animations[FighterState::Backward] = ActionInit(4,"Backward");
        animations[FighterState::Forward] = ActionInit(4,"Forward");
        animations[FighterState::JumpUP] = ActionInit(11, "JumpUP");
        animations[FighterState::JumpForward] = ActionInit(10, "JumpForward");
        std::vector<std::string> reversedAnimations = animations[FighterState::JumpForward];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::JumpBackward] = reversedAnimations;
        animations[FighterState::Crouch] = ActionInit(1, "Crouch");
        animations[FighterState::CrouchDown] = ActionInit(2, "CrouchDown");
        reversedAnimations = animations[FighterState::CrouchDown];
        std::reverse(reversedAnimations.begin(), reversedAnimations.end());
        animations[FighterState::CrouchUp] = reversedAnimations;
        animations[FighterState::LP] = ActionInit(5, "LP");
        animations[FighterState::MP] = ActionInit(7, "MP");
        animations[FighterState::HP] = ActionInit(9, "HP");
        animations[FighterState::LK] = ActionInit(7, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(9, "HK");

        animations[FighterState::HurtHeadL] = animations[FighterState::HurtHeadM] = animations[FighterState::HurtHeadH] =ActionInit(2, "HurtHead");
        animations[FighterState::HurtBodyL] = animations[FighterState::HurtBodyM] = animations[FighterState::HurtBodyH] = ActionInit(2, "HurtBody");

        animations[FighterState::BackwardBlock]=ActionInit(2, "BackwardBlock");
        animations[FighterState::CrouchBlock]=ActionInit(2, "CrouchBlock");

        animations[FighterState::CrouchLP] = ActionInit(3, "CrouchLP");
        animations[FighterState::CrouchMP] = ActionInit(5, "CrouchMP");
        animations[FighterState::CrouchHP] = ActionInit(7, "CrouchHP");
        animations[FighterState::CrouchLK] = ActionInit(5, "CrouchLK");
        animations[FighterState::CrouchMK] = animations[FighterState::CrouchLK];
        animations[FighterState::CrouchHK] = ActionInit(5, "CrouchHK");

        animations[FighterState::WinStart]=ActionInit(1, "WinStart");
        animations[FighterState::Win]=ActionInit(2, "Win");

        animations[FighterState::TimeOverLoss]=ActionInit(1, "TimeOverLoss");
        animations[FighterState::DefeatedLoss]=ActionInit(3, "DefeatedLoss");

        frames[FighterState::Idle]={100, 150, 150, 100};
        frames[FighterState::Forward]={120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120};
        frames[FighterState::JumpUP]={60,60,60,60,60,60,60,60,60,60,60};
        frames[FighterState::JumpForward]={60,60,60,60,60,60,60,60,60,60,};
        frames[FighterState::JumpBackward]={60,60,60,60,60,60,60,60,60,60};
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60};
        frames[FighterState::CrouchUp]={60,60};
        frames[FighterState::LP]={60,60,60,60,60};
        frames[FighterState::MP]={60,60,60,60,60,60,60};
        frames[FighterState::HP]={60,60,60,60,60,60,60,60,60};
        frames[FighterState::LK]={60,60,60,60,60,60,60};
        frames[FighterState::MK]={60,60,60,60,60};
        frames[FighterState::HK]={60,60,60,60,60,60,60,60,60};

        frames[FighterState::CrouchLP]={60,90,60};
        frames[FighterState::CrouchMP]={60,60,60,60,60};
        frames[FighterState::CrouchHP]={60,60,60,60,60,60,60};
        frames[FighterState::CrouchLK]={60,60,60,60,60};
        frames[FighterState::CrouchMK]={60,60,60,60,60};
        frames[FighterState::CrouchHK]={60,60,60,60,60};

        frames[FighterState::HurtHeadL] = {100,100};
        frames[FighterState::HurtHeadM] = {150,150};
        frames[FighterState::HurtHeadH] = {200,200};
        frames[FighterState::HurtBodyL] = {100,100};
        frames[FighterState::HurtBodyM] = {150,150};
        frames[FighterState::HurtBodyH] = {200,200};

        frames[FighterState::BackwardBlock] = {150,150};
        frames[FighterState::CrouchBlock] = {150,150};

        frames[FighterState::WinStart]={180};
        frames[FighterState::Win]={180,180};

        frames[FighterState::TimeOverLoss]={180};
        frames[FighterState::DefeatedLoss]={180,180,180};
    }
    void Honda::LoadOffsetVelocity() {
        offset[FighterState::Idle]={{-3,0},{3,-3},{13,-10},{5,-2}};
        offset[FighterState::Crouch]={{1,-32}};
        offset[FighterState::CrouchDown]={{-5,-12},{3,-23}};
        offset[FighterState::CrouchUp]={{3,-23},{-5,-12}};
        //Stand attack offset
        offset[FighterState::LP]={{-11,2},{18,0},{50,-10},{9,1},{-21,2}};
        offset[FighterState::MP]={{-3,3},{-19,-2},{4,-12},{36,-9},{0,-11},{-22,-1},{-3,4}};
        offset[FighterState::HP]={{1,4},{-14,35},{9,43},{93,-2},{29,-5},{94,-1},{7,41},{-9,32},{5,4}};
        offset[FighterState::LK]={{-5,2},{12,26},{56,28},{202,13},{51,25},{3,24},{-5,4}};
        offset[FighterState::MK]={{-2,-1},{33,0},{118,-20},{29,0},{-2,-3}};
        offset[FighterState::HK]={{-4,-1},{17,26},{38,44},{66,44},{84,51},{70,48},{30,43},{15,23},{-4,1}};
        //Crouch attack offset
        offset[FighterState::CrouchLP]={{49,-24},{85,-30},{50,-25}};
        offset[FighterState::CrouchMP]={{-2,-25},{20,-30},{50,-25},{23,-34},{-9,-24}};
        offset[FighterState::CrouchHP]={{2,-50},{26,-30},{-10,-33},{-12,-25},{-6,-37},{24,-30},{4,-47}};
        offset[FighterState::CrouchLK]={{10,-19},{23,-25},{76,-25},{20,-24},{14,-23}};
        offset[FighterState::CrouchMK]=offset[FighterState::CrouchLK];
        offset[FighterState::CrouchHK]={{19,-28},{60,-26},{6,-49},{-204,-37},{-126,-32}};

        offset[FighterState::HurtHeadL]=offset[FighterState::HurtHeadM]=offset[FighterState::HurtHeadH]={{-4,7},{-38,1}};
        offset[FighterState::HurtBodyL]=offset[FighterState::HurtBodyM]=offset[FighterState::HurtBodyH]={{10,0},{-7,-6}};

        offset[FighterState::BackwardBlock]={{-18,5},{-33,20}};
        offset[FighterState::CrouchBlock]={{6,-23},{-9,-26}};

        offset[FighterState::Win]={{2,8},{-5,66}};
        offset[FighterState::WinStart]={{-13,-10}};

        offset[FighterState::TimeOverLoss]={{5,-7}};
        offset[FighterState::DefeatedLoss]={{-39,-2},{-68,-67},{-153,-78}};
    }
    void Honda::LoadAllBox() {

        boxes.pushbox.size[FighterState::Idle]={150,200};
        boxes.pushbox.offset[FighterState::Idle]={5,0};
        boxes.pushbox.size[FighterState::Crouch]=boxes.pushbox.size[FighterState::CrouchDown]=boxes.pushbox.size[FighterState::CrouchUp]={150,120};
        boxes.pushbox.offset[FighterState::Crouch]=boxes.pushbox.offset[FighterState::CrouchDown]=boxes.pushbox.offset[FighterState::CrouchUp]={15,-43};

        boxes.hurtbox.head.size[FighterState::Idle]={{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::Idle]={{190,100},{190,100},{190,100},{190,100}};
        boxes.hurtbox.leg.size[FighterState::Idle]={{250,125},{250,125},{250,125},{250,125}};
        boxes.hurtbox.head.offset[FighterState::Idle]={{42,96},{36,91},{35,82},{38,90}};
        boxes.hurtbox.body.offset[FighterState::Idle]={{8,35},{10,27},{25,20},{9,31}};
        boxes.hurtbox.leg.offset[FighterState::Idle]={{-13,-67},{-7,-63},{8,-61},{-7,-65}};
        //Crouch
        boxes.hurtbox.head.size[FighterState::Crouch]={{50,50}};
        boxes.hurtbox.body.size[FighterState::Crouch]={{190,80}};
        boxes.hurtbox.leg.size[FighterState::Crouch]={{250,70}};
        boxes.hurtbox.head.offset[FighterState::Crouch]={{67,59}};
        boxes.hurtbox.body.offset[FighterState::Crouch]={{25,12}};
        boxes.hurtbox.leg.offset[FighterState::Crouch]={{-3,-56}};

        boxes.hurtbox.head.size[FighterState::CrouchDown]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchDown]={{190,80},{190,80}};
        boxes.hurtbox.leg.size[FighterState::CrouchDown]={{250,100},{250,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchDown]={{50,82},{67,59}};
        boxes.hurtbox.body.offset[FighterState::CrouchDown]={{7,27},{25,12}};
        boxes.hurtbox.leg.offset[FighterState::CrouchDown]={{-9,-56},{-3,-56}};

        boxes.hurtbox.head.size[FighterState::CrouchUp]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchUp]={{190,80},{190,80}};
        boxes.hurtbox.leg.size[FighterState::CrouchUp]={{250,50},{250,50}};
        boxes.hurtbox.head.offset[FighterState::CrouchUp]={{67,59},{50,82}};
        boxes.hurtbox.body.offset[FighterState::CrouchUp]={{25,12},{7,27}};
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]={{-3,-56},{-9,-56}};
        //block
        boxes.hurtbox.head.size[FighterState::CrouchBlock]={{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchBlock]={{190,90},{190,90}};
        boxes.hurtbox.leg.size[FighterState::CrouchBlock]={{230,90},{220,90}};
        boxes.hurtbox.head.offset[FighterState::CrouchBlock]={{31,74},{12,70}};
        boxes.hurtbox.body.offset[FighterState::CrouchBlock]={{2,16},{-6,6}};
        boxes.hurtbox.leg.offset[FighterState::CrouchBlock]={{-25,-55},{-23,-67}};

        boxes.hurtbox.head.offset[FighterState::BackwardBlock]={{5,102},{-49,133}};
        boxes.hurtbox.body.size[FighterState::BackwardBlock]={{190,100},{120,100}};
        boxes.hurtbox.body.offset[FighterState::BackwardBlock]={{-7,35},{-57,52}};

        //hurtbox Crouch Attack
        boxes.hurtbox.head.size[FighterState::CrouchLP]={{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLP]={{200,70},{200,70},{200,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLP]={{240,70},{240,70},{240,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLP]={{44,62},{60,43},{45,54}};
        boxes.hurtbox.body.offset[FighterState::CrouchLP]={{-14,8},{18,4},{-7,4}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLP]={{-62,-53},{-39,-55},{-49,-55}};

        boxes.hurtbox.head.size[FighterState::CrouchLK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchLK]={{200,70},{200,70},{200,70},{200,70},{200,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchLK]={{240,70},{240,70},{240,70},{240,70},{240,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchLK]={{2,66},{-6,56},{-2,49},{-7,57},{10,63}};
        boxes.hurtbox.body.offset[FighterState::CrouchLK]={{-8,13},{-6,10},{5,-1},{0,3},{1,5}};
        boxes.hurtbox.leg.offset[FighterState::CrouchLK]={{-14,-67},{-11,-69},{-2,-71},{-8,-75},{-4,-71}};

        boxes.hurtbox.head.size[FighterState::CrouchMP]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchMP]={{200,70},{220,70},{220,70},{220,70},{200,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchMP]={{240,70},{240,70},{240,70},{240,70},{240,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchMP]={{91,59},{92,49},{73,56},{97,46},{85,57}};
        boxes.hurtbox.body.offset[FighterState::CrouchMP]={{26,3},{8,1},{8,10},{14,2},{12,5}};
        boxes.hurtbox.leg.offset[FighterState::CrouchMP]={{2,-64},{-8,-67},{-16,-64},{4,-66},{0,-65}};

        boxes.hurtbox.head.size[FighterState::CrouchMK]=boxes.hurtbox.head.size[FighterState::CrouchLK];
        boxes.hurtbox.body.size[FighterState::CrouchMK]=boxes.hurtbox.body.size[FighterState::CrouchLK];
        boxes.hurtbox.leg.size[FighterState::CrouchMK]=boxes.hurtbox.leg.size[FighterState::CrouchLK];
        boxes.hurtbox.head.offset[FighterState::CrouchMK]=boxes.hurtbox.head.offset[FighterState::CrouchLK];
        boxes.hurtbox.body.offset[FighterState::CrouchMK]=boxes.hurtbox.body.offset[FighterState::CrouchLK];
        boxes.hurtbox.leg.offset[FighterState::CrouchMK]=boxes.hurtbox.leg.offset[FighterState::CrouchLK];

        boxes.hurtbox.head.size[FighterState::CrouchHP]={{50,50},{50,50},{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHP]={{200,70},{200,70},{200,70},{200,70},{200,70},{200,70},{200,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHP]={{230,70},{230,70},{230,70},{230,70},{230,70},{230,70},{230,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchHP]={{36,65},{46,77},{73,66},{102,57},{81,64},{43,74},{37,67}};
        boxes.hurtbox.body.offset[FighterState::CrouchHP]={{12,24},{16,28},{30,27},{36,23},{32,20},{11,27},{14,11}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHP]={{-18,-49},{-17,-37},{-13,-35},{-7,-40},{-6,-47},{-18,-44},{-13,-55}};

        boxes.hurtbox.head.size[FighterState::CrouchHK]={{50,50},{50,50},{50,50},{50,50},{50,50}};
        boxes.hurtbox.body.size[FighterState::CrouchHK]={{200,70},{200,70},{150,70},{170,70},{160,70}};
        boxes.hurtbox.leg.size[FighterState::CrouchHK]={{230,70},{250,70},{180,70},{180,70},{180,70}};
        boxes.hurtbox.head.offset[FighterState::CrouchHK]={{9,64},{-29,72},{-101,48},{-125,69},{-80,66}};
        boxes.hurtbox.body.offset[FighterState::CrouchHK]={{-19,6},{-25,13},{-53,7},{-170,18},{-137,17}};
        boxes.hurtbox.leg.offset[FighterState::CrouchHK]={{-18,-55},{-14,-57},{-30,-72},{-191,-69},{-154,-57}};
        //hurtbox Stand Attack
        boxes.hurtbox.body.size[FighterState::HP]={{190,100},{150,100},{160,100},{190,100},{220,80},{190,100},{160,100},{150,100},{190,100}};
        boxes.hurtbox.head.offset[FighterState::HP]={{37,88},{67,94},{61,99},{91,71},{125,49},{93,73},{60,98},{72,93},{40,90}};
        boxes.hurtbox.body.offset[FighterState::HP]={{-5,27},{-6,41},{6,42},{11,30},{59,1},{16,28},{15,36},{-9,39},{5,31}};
        boxes.hurtbox.leg.offset[FighterState::HP]={{-19,-67},{-25,-64},{-16,-65},{-12,-70},{13,-68},{-8,-66},{-15,-65},{-4,-69},{-11,-76}};

        boxes.hurtbox.body.size[FighterState::LK]={{190,100},{190,100},{140,100},{140,100},{140,100},{190,100},{190,100}};
        boxes.hurtbox.leg.size[FighterState::LK]={{220,100},{220,100},{140,100},{220,100},{140,100},{220,100},{220,100}};
        boxes.hurtbox.head.offset[FighterState::LK]={{38,89},{81,107},{93,119},{111,99},{87,116},{69,109},{34,91}};
        boxes.hurtbox.body.offset[FighterState::LK]={{-2,28},{31,43},{63,51},{114,33},{63,56},{41,41},{-3,35}};
        boxes.hurtbox.leg.offset[FighterState::LK]={{-11,-79},{10,-59},{107,-69},{127,-70},{99,-70},{5,-70},{-4,-77}};

        boxes.hurtbox.head.offset[FighterState::MK]={{40,89},{86,93},{162,52},{84,90},{39,87}};
        boxes.hurtbox.body.offset[FighterState::MK]={{4,24},{47,32},{88,-1},{52,34},{4,22}};
        boxes.hurtbox.leg.offset[FighterState::MK]={{-13,-72},{-1,-69},{50,-75},{4,-73},{-14,-69}};

        boxes.hurtbox.body.size[FighterState::HK]={{190,100},{190,100},{140,100},{120,100},{120,100},{120,100},{140,100},{190,100},{190,100}};
        boxes.hurtbox.leg.size[FighterState::HK]={{220,100},{210,100},{120,220},{60,220},{60,220},{60,220},{120,200},{210,100},{220,100}};
        boxes.hurtbox.head.offset[FighterState::HK]={{34,92},{80,113},{89,149},{35,157},{17,172},{41,164},{80,149},{82,110},{40,91}};
        boxes.hurtbox.body.offset[FighterState::HK]={{-9,24},{40,49},{54,98},{3,109},{12,120},{18,109},{51,89},{42,45},{-9,32}};
        boxes.hurtbox.leg.offset[FighterState::HK]={{-22,-71},{17,-50},{56,-43},{72,-49},{68,-45},{76,-48},{49,-53},{21,-55},{-19,-73}};
        //hitbox Crouch Attack
        boxes.hitbox.size[FighterState::CrouchLP]={150,50};
        boxes.hitbox.offset[FighterState::CrouchLP]={{-1,-1},{191,41},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMP]={150,60};
        boxes.hitbox.offset[FighterState::CrouchMP]={{-1,-1},{-1,-1},{200,64},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchHP]={160,50};
        boxes.hitbox.offset[FighterState::CrouchHP]={{-1,-1},{180,30},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchLK]={150,60};
        boxes.hitbox.offset[FighterState::CrouchLK]={{-1,-1},{-1,-1},{210,72},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::CrouchMK]=boxes.hitbox.size[FighterState::CrouchLK];
        boxes.hitbox.offset[FighterState::CrouchMK]=boxes.hitbox.offset[FighterState::CrouchLK];
        boxes.hitbox.size[FighterState::CrouchHK]={140,50};
        boxes.hitbox.offset[FighterState::CrouchHK]={{-1,-1},{180,-84},{-1,-1},{-1,-1},{-1,-1}};
        //hitbox Stand Attack
        boxes.hitbox.size[FighterState::LP]={170,50};
        boxes.hitbox.offset[FighterState::LP]={{-1,-1},{-1,-1},{201,60},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MP]={140,50};
        boxes.hitbox.offset[FighterState::MP]={{-1,-1},{-1,-1},{-1,-1},{185,64},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HP]={220,50};
        boxes.hitbox.offset[FighterState::HP]={{-1,-1},{-1,-1},{-1,-1},{225,24},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::LK]={180,60};
        boxes.hitbox.offset[FighterState::LK]={{-1,-1},{-1,-1},{-1,-1},{315,-45},{-1,-1},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::MK]={200,60};
        boxes.hitbox.offset[FighterState::MK]={{-1,-1},{-1,-1},{250,-100},{-1,-1},{-1,-1}};
        boxes.hitbox.size[FighterState::HK]={220,60};
        boxes.hitbox.offset[FighterState::HK]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{185,125},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
    }
    void Honda::LoadSpecialMove() {
        animations[FighterState::Special_1]=ActionInit(6, "Special_1");
        animations[FighterState::SpecialRecovery_1]=ActionInit(6, "SpecialRecovery_1");
        offset[FighterState::Special_1]={{0,-4},{-9,7},{-13,14},{-3,15},{5,-6},{38,30}};
        offset[FighterState::SpecialRecovery_1]={{-2,59},{-23,88},{9,22},{2,-36},{3,-26},{-2,-14}};
        frames[FighterState::SpecialRecovery_1]={90,60,34,34,17,17};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::LP]={30,30,30,30,90,420};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::MP]={30,30,30,30,120,560};
        SpecialMoveData.animationData[FighterState::Special_1].frames[Keys::HP]={30,30,30,30,150,720};

        boxes.hurtbox.body.size[FighterState::Special_1]={{190,100},{190,100},{160,100},{160,100},{190,100},{190,100}};
        boxes.hurtbox.leg.size[FighterState::Special_1]={{250,125},{250,125},{250,125},{250,125},{230,125},{150,50}};
        boxes.hurtbox.head.offset[FighterState::Special_1]={{42,94},{1,112},{-43,130},{30,128},{93,91},{200,9}};
        boxes.hurtbox.body.offset[FighterState::Special_1]={{5,26},{-18,35},{-55,54},{-7,58},{46,43},{83,27}};
        boxes.hurtbox.leg.offset[FighterState::Special_1]={{-6,-71},{-13,-68},{-21,-64},{-6,-68},{28,-65},{-68,19}};

        boxes.hurtbox.body.size[FighterState::SpecialRecovery_1]={{190,100},{190,100},{190,100},{190,100},{190,100},{190,100}};
        boxes.hurtbox.leg.size[FighterState::SpecialRecovery_1]={{100,125},{50,125},{220,125},{250,125},{250,125},{250,125}};
        boxes.hurtbox.head.offset[FighterState::SpecialRecovery_1]={{121,14},{-77,4},{-115,4},{74,28},{64,47},{54,74}};
        boxes.hurtbox.body.offset[FighterState::SpecialRecovery_1]={{52,87},{-8,54},{-22,-35},{15,-7},{17,-4},{9,21}};
        boxes.hurtbox.leg.offset[FighterState::SpecialRecovery_1]={{-81,54},{-73,119},{61,69},{10,-77},{7,-71},{1,-67}};

        boxes.hitbox.size[FighterState::Special_1]={150,100};
        boxes.hitbox.offset[FighterState::Special_1]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{170,25}};

        StateEnter[FighterState::Special_1]=[this] { HeadbuttStateEnter(); };
        StateUpdate[FighterState::Special_1]=[this] { HeadbuttStateUpdate(); };
        StateEnter[FighterState::SpecialRecovery_1]=[this] { HeadbuttRecoveryStateEnter(); };
        StateUpdate[FighterState::SpecialRecovery_1]=[this] { HeadbuttRecoveryStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_1].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Honda/SP1.wav");

        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::LP]={9,0};
        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::MP]={12,0};
        SpecialMoveData.animationData[FighterState::Special_1].initialvelocitys[Keys::HP]={15,0};

        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::LP]=10;
        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::MP]=15;
        SpecialMoveData.attackdata[FighterState::Special_1].attack[Keys::HP]=20;

        SpecialMoveData.attackdata[FighterState::Special_1].HitStrength[Keys::LP]=HitStrength::H;

        SpecialMoveData.SkillCommand[FighterState::Special_1].command={
            SpecialMoveDirection::Forward,
            SpecialMoveDirection::Backward
        };
        SpecialMoveData.SkillCommand[FighterState::Special_1].requiredAttack=AttackButton::ANY_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_1].commandtype=CommandType::Pressed;
        SpecialMoveData.SkillCommand[FighterState::Special_1].chargetime[Keys::LP]=250;
        SpecialMoveData.SkillCommand[FighterState::Special_1].chargetime[Keys::MP]=500;
        SpecialMoveData.SkillCommand[FighterState::Special_1].chargetime[Keys::HP]=750;
        SpecificStates.borderCheckStates.insert(FighterState::Special_1);

        animations[FighterState::Special_2]=ActionInit(10, "Special_2");
        offset[FighterState::Special_2]={{5,3},{41,1},{117,-2},{63,14},{112,-10},{84,-11},{126,11},{54,-12},{46,-2},{4,0}};

        SpecialMoveData.animationData[FighterState::Special_2].frames[Keys::LP]={60,120,180,120,180,120,180,120,120,60};
        boxes.hurtbox.head.offset[FighterState::Special_2]={{43,97},{61,88},{72,75},{79,68},{83,69},{83,68},{83,68},{84,68},{63,86},{39,91}};
        boxes.hurtbox.body.offset[FighterState::Special_2]={{5,32},{11,35},{10,34},{24,16},{24,21},{30,16},{18,26},{22,19},{13,30},{-5,32}};
        boxes.hurtbox.leg.offset[FighterState::Special_2]={{-7,-74},{-5,-69},{14,-49},{29,-53},{29,-54},{26,-58},{27,-57},{27,-57},{7,-68},{-12,-67}};

        boxes.hitbox.size[FighterState::Special_2]={200,100};
        boxes.hitbox.offset[FighterState::Special_2]={{-1,-1},{-1,-1},{274,54},{187,85},{243,-17},{207,15},{271,85},{152,-44},{-1,-1},{-1,-1}};

        SpecialMoveData.attackdata[FighterState::Special_2].attack[Keys::LP]=5;

        SpecialMoveData.attackdata[FighterState::Special_2].HitStrength[Keys::LP]=HitStrength::H;

        StateEnter[FighterState::Special_2]=[this] { HundredSlapStateEnter(); };
        StateUpdate[FighterState::Special_2]=[this] { HundredSlapStateUpdate(); };

        SpecialMoveData.sounddata[FighterState::Special_2].sound[Keys::LP]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Honda/SP2.wav");

        SpecialMoveData.SkillCommand[FighterState::Special_2].command={};
        SpecialMoveData.SkillCommand[FighterState::Special_2].requiredAttack=AttackButton::ALL_PUNCH;
        SpecialMoveData.SkillCommand[FighterState::Special_2].commandtype=CommandType::Null;

        soundeffect[FighterState::WinStart]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Honda/Win.wav");
        soundeffect[FighterState::DefeatedLoss]=std::make_shared<SFX>(RESOURCE_DIR"/voice/SF6/Honda/Loss.wav");
    }
    void Honda::HeadbuttStateEnter() {
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        SkillErrorPrevent(ButtonType,ButtonList::punch);
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Honda::HeadbuttStateUpdate() {
        if(ActionNow->GetCurrentFrameIndex()==5&&HitEnemy) {
            ClearButtonType();
            ChangeState(FighterState::SpecialRecovery_1);
        }
        if(ActionNow->GetCurrentFrameIndex()>=5) {
            velocity=GetInitialvelocity();
        }
        if (GetAnimationIsEnd()) {
            ClearButtonType();
            ChangeState(FighterState::SpecialRecovery_1);
        }
    }
    void Honda::HeadbuttRecoveryStateEnter() {
        ResetVelocity();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Honda::HeadbuttRecoveryStateUpdate() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
    void Honda::HundredSlapStateEnter() {
        ResetVelocity();
        ButtonType=controller->GetCurrentAttackKey();
        LoadCurrentSpecialMove(ButtonType);
        PlayCurrentSound();
        SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
    }
    void Honda::HundredSlapStateUpdate() {
        if (GetAnimationIsEnd()) {ChangeState(FighterState::Idle);}
    }
}