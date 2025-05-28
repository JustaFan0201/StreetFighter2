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

        frames[FighterState::Idle]={120, 150, 150, 120};
        frames[FighterState::Forward]=frames[FighterState::Backward]={120, 150, 150, 120};
        frames[FighterState::JumpUP]=frames[FighterState::JumpForward]={90,120,150,120,90};
        std::vector<int> reversedframe = frames[FighterState::JumpForward];
        std::reverse(reversedframe.begin(), reversedframe.end());
        frames[FighterState::JumpBackward] = reversedframe;
        frames[FighterState::Crouch]={60};
        frames[FighterState::CrouchDown]={60,60};
        frames[FighterState::CrouchUp]={60,60};
    }
    void Vega::LoadOffsetVelocity() {
        offset[FighterState::Idle]={{0,0},{0,-2},{-3,-7},{-1,-4}};
        offset[FighterState::Crouch]={{-1,-52}};
        offset[FighterState::CrouchDown]={{-1,-10},{1,-38}};
        offset[FighterState::CrouchUp]={{1,-38},{-1,-10}};

        offset[FighterState::JumpUP]=offset[FighterState::JumpForward]={{0,0},{-15,3},{-39,16},{-17,7},{1,2}};
        std::vector<glm::vec2> reversedoffset = offset[FighterState::JumpForward];
        std::reverse(reversedoffset.begin(), reversedoffset.end());
        offset[FighterState::JumpBackward]=reversedoffset;
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

        std::vector<glm::vec2> reversedhurtbox = boxes.hurtbox.head.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.head.offset[FighterState::CrouchUp]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.body.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.body.offset[FighterState::CrouchUp]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.leg.offset[FighterState::CrouchDown];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.leg.offset[FighterState::CrouchUp]=reversedhurtbox;

        //hurtbox Jump
        boxes.hurtbox.body.size[FighterState::JumpUP]={{100,100},{100,100},{100,100},{100,100},{100,100}};
        boxes.hurtbox.leg.size[FighterState::JumpUP]={{100,150},{120,125},{140,125},{140,125},{100,125}};
        boxes.hurtbox.head.offset[FighterState::JumpUP]=boxes.hurtbox.head.offset[FighterState::JumpForward]={{26,115},{20,103},{-7,83},{17,107},{25,121}};
        boxes.hurtbox.body.offset[FighterState::JumpUP]=boxes.hurtbox.body.offset[FighterState::JumpForward]={{2,56},{-7,48},{-42,39},{-8,47},{3,58}};
        boxes.hurtbox.leg.offset[FighterState::JumpUP]=boxes.hurtbox.leg.offset[FighterState::JumpForward]={{-3,-35},{-4,-36},{-24,-22},{-2,-33},{-1,-47}};

        reversedhurtbox = boxes.hurtbox.head.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.head.offset[FighterState::JumpBackward]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.body.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.body.offset[FighterState::JumpBackward]=reversedhurtbox;

        reversedhurtbox = boxes.hurtbox.leg.offset[FighterState::JumpForward];
        std::reverse(reversedhurtbox.begin(), reversedhurtbox.end());
        boxes.hurtbox.leg.offset[FighterState::JumpBackward]=reversedhurtbox;
    }
    void Vega::LoadSpecialMove() {

    }
}