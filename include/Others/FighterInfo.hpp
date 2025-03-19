//
// Created by asus on 2025/3/12.
//

#ifndef FIGHTERINFO_HPP
#define FIGHTERINFO_HPP

namespace Util {
    enum class FighterDirection {
        Left  = 1,
        Right = -1
    };
    constexpr float StageFloor = -320.0f;
    struct velocity {
        int x=0;
        int y=0;
    };
    enum class FighterState {
        Idle,
        Forward,
        Backward,
        JumpUP,
        JumpForward,
        JumpBackward,
        Squatdown,
        SquatdownBackward,
        LP,
        MP,
        HP,
        LK,
        MK,
        HK,
        SquatdownLP,
        SquatdownMP,
        SquatdownHP,
        SquatdownLK,
        SquatdownMK,
        SquatdownHK,
        JumpLP,
        JumpMP,
        JumpHP,
        JumpLK,
        JumpMK,
        JumpHK
    };
    struct Initialvelocity {
        std::unordered_map<FighterState,float> x;
        std::unordered_map<FighterState,float> y;
    };
}

#endif //FIGHTERINFO_HPP
