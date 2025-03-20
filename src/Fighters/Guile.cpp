//
// Created by asus on 2025/2/27.
//

#include "Fighters/Guile.hpp"
namespace Util {
    Guile::Guile():Fighter("Guile",{0,0}){
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Guile/Guile_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/usa.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/GuileTheme.mp3");
        m_name = "Guile";
        country_position={{350, 140},0,{1,1}};
        BackgroundInit(5);
        Guile::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );
    }
    void Guile::LoadAnimations() {
        animations[FighterState::Idle]=ActionInit(6,"Idle");
        animations[FighterState::Backward]=ActionInit(5,"Backward");
        animations[FighterState::Forward]=ActionInit(5,"Forward");
        animations[FighterState::LP]=ActionInit(3,"LP");
        animations[FighterState::MP]=ActionInit(5, "MP");
    }
}