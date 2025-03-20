//
// Created by asus on 2025/2/27.
//

#include "Fighters/Chunli.hpp"
namespace Util {
    Chunli::Chunli(): Fighter("Chunli",{0,0}) {
        face=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Chunli/Chunli_face.png");
        nametag=std::string(RESOURCE_DIR"/ScenePicture/Fighters/Chunli/Chunli_nametag.png");
        country=std::string(RESOURCE_DIR"/ScenePicture/slect/china.png");
        m_BGM=std::make_shared<BGM>(RESOURCE_DIR"/music/Theme/ChunliTheme.mp3");
        m_name = "Chunli";
        country_position={{-113, 193},0,{1,1}};
        BackgroundInit(29);
        Chunli::LoadAnimations();
        ActionNow = std::make_shared<AnimationSpace>(
            animations[FighterState::Idle],
            true,
            60,
            true,
            5
        );

    }
    void Chunli::LoadAnimations() {
        animations[FighterState::Idle]=ActionInit(4,"Idle");
        animations[FighterState::Backward]=ActionInit(12,"Backward");
        animations[FighterState::Forward]=ActionInit(12,"Forward");
        animations[FighterState::LP]=ActionInit(5,"LP");
        animations[FighterState::MP]=ActionInit(5, "MP");
    }
}