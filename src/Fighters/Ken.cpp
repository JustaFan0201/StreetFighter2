//
// Created by asus on 2025/2/27.
//

#include "Fighters/Ken.hpp"
namespace Util {
    Ken::Ken(): Fighter("Ken",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ken/Ken_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Ken/Ken_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/KenTheme.mp3");
        country_position={{338, 245},0,{1,1}};
        BackgroundInit(14);
        StateInit();
        Ken::LoadAnimations();
        Ken::LoadOffsetVelocity();
        Ken::LoadAllBox();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            false,
            60,
            true,
            5
        );
        BlackPicture=std::make_shared<AnimationSpace>(
                std::vector<std::string> {RESOURCE_DIR"/EditMaterial/black.png"},
                true,
                120,
                true,
                6
                );
    }
    void Ken::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(6,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(4, "MP");
        animations[FighterState::JumpUP] = ActionInit(8, "JumpUP");
        animations[FighterState::LK] = ActionInit(5, "LK");
        animations[FighterState::MK] = ActionInit(5, "MK");
        animations[FighterState::HK] = ActionInit(5, "HK");


        frames[FighterState::Idle]={100, 150, 200, 150, 100,120};
        frames[FighterState::Forward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::Backward]={120, 120, 120, 120, 120, 120};
        frames[FighterState::LP]={180,240,180};
        frames[FighterState::MP]={120,120,300};
        frames[FighterState::JumpUP]={120,120,120,120,120,120,120,120};
        frames[FighterState::LK]={100,100,100,100,100};
        frames[FighterState::MK]={100,100,120,100,100};
        frames[FighterState::HK]={120,120,120,120,120};
    }
    void Ken::LoadOffsetVelocity() {
        Initialvelocity.x[FighterState::Forward]=400;
        Initialvelocity.x[FighterState::Backward]=-400;
        Initialvelocity.x[FighterState::JumpForward]=500;
        Initialvelocity.x[FighterState::JumpBackward]=-500;
        Initialvelocity.y[FighterState::JumpForward]=2100;
        Initialvelocity.y[FighterState::JumpBackward]=2100;
        Initialvelocity.y[FighterState::JumpUP]=2000;

        offset[FighterState::Idle]={{0,0},{0,0},{0,0},{0,0},{0,0}};
    }
    void Ken::LoadAllBox() {
        pushbox.size[FighterState::Idle]={100,200};
    }
}