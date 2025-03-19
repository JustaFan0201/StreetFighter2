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
        Ken::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Ken::LoadAnimations() {
        animations[FighterState::Idle] = ActionInit(5,"Idle");
        animations[FighterState::Backward] = ActionInit(6,"Backward");
        animations[FighterState::Forward] = ActionInit(6,"Forward");
        animations[FighterState::LP] = ActionInit(3, "LP");
        animations[FighterState::MP] = ActionInit(3, "MP");
    }

}