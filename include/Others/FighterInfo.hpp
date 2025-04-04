//
// Created by asus on 2025/3/12.
//

#ifndef FIGHTERINFO_HPP
#define FIGHTERINFO_HPP

namespace Util {
    constexpr float StageFloor = -320.0f;
    enum class FighterDirection {
        Left  = 1,
        Right = -1
    };
    struct velocity {
        float x=0;
        float y=0;
    };
    enum class FighterState {
        Idle,
        Forward,
        Backward,
        JumpUP,
        JumpForward,
        JumpBackward,
        Crouch,
        CrouchDown,
        CrouchUp,
        LP,
        MP,
        HP,
        LK,
        MK,
        HK,
        CrouchLP,
        CrouchMP,
        CrouchHP,
        CrouchLK,
        CrouchMK,
        CrouchHK,
        JumpLP,
        JumpMP,
        JumpHP,
        JumpLK,
        JumpMK,
        JumpHK,
        Special_1,
        Special_2,
        Special_3,
        HurtHeadL,
        HurtHeadM,
        HurtHeadH,
        HurtBodyL,
        HurtBodyM,
        HurtBodyH,
        BackwardBlock,
        CrouchBlock
    };
    enum class HitLocation {
        Null=-1,
        Head = 0,
        Body = 1,
        Leg = 2
    };
    enum class HitStrength {
        Null=-1,
        L = 0,
        M = 1,
        H = 2
    };
    struct Initialvelocity {
        std::unordered_map<FighterState,float> x;
        std::unordered_map<FighterState,float> y;
    };
    struct HurtBoxPart {
        std::unordered_map<FighterState, std::vector<glm::vec2>> size;
        std::unordered_map<FighterState, std::vector<glm::vec2>> offset;
    };
    struct HurtBox {
        HurtBoxPart head;
        HurtBoxPart body;
        HurtBoxPart leg;
    };
    struct PushBox {
        std::unordered_map<FighterState, glm::vec2> size;
        std::unordered_map<FighterState, glm::vec2> offset;
    };
    struct HitBox {
        std::unordered_map<FighterState, glm::vec2> size;
        std::unordered_map<FighterState, std::vector<glm::vec2>> offset;
    };
    struct Boxes {
        PushBox pushbox;
        HurtBox hurtbox;
        HitBox hitbox;
    };

    inline bool RectangleOverlap(glm::vec2 Rec1_position, glm::vec2 Rec1_HW,
                                 glm::vec2 Rec2_position, glm::vec2 Rec2_HW) {

        float Rec1_Left   = Rec1_position.x - Rec1_HW.x / 2;
        float Rec1_Right  = Rec1_position.x + Rec1_HW.x / 2;
        float Rec1_Top    = Rec1_position.y + Rec1_HW.y / 2;
        float Rec1_Bottom = Rec1_position.y - Rec1_HW.y / 2;

        float Rec2_Left   = Rec2_position.x - Rec2_HW.x / 2;
        float Rec2_Right  = Rec2_position.x + Rec2_HW.x / 2;
        float Rec2_Top    = Rec2_position.y + Rec2_HW.y / 2;
        float Rec2_Bottom = Rec2_position.y - Rec2_HW.y / 2;

        return (Rec1_Left < Rec2_Right) &&
                (Rec1_Right > Rec2_Left) &&
                (Rec1_Top > Rec2_Bottom) &&
                (Rec1_Bottom < Rec2_Top);
    }
}

#endif //FIGHTERINFO_HPP