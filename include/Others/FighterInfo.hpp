//
// Created by asus on 2025/3/12.
//

#ifndef FIGHTERINFO_HPP
#define FIGHTERINFO_HPP
namespace Util {
    constexpr float StageFloor = -310.0f;
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
        CrouchBlock,
        WinStart,
        Win,
        Loss
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
    enum class PlayerType {
        Null,
        Player1,
        Player2,
        Ai
    };
    enum class ControllerState {
        Pause,
        Active
    };
    enum class Keys {
        Null,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        LP,
        MP,
        HP,
        LK,
        MK,
        HK
    };
    enum class SpecialMoveDirection {
        Backward_down=1,
        down=2,
        Forward_down=3,
        Backward=4,
        Null=5,
        Forward=6,
        Backward_up=7,
        Up=8,
        Forward_up=9
    };
    enum class AttackButton {
        LP, MP, HP,
        LK, MK, HK,
        ANY_PUNCH,
        ANY_KICK,
        ALL_PUNCH,
        ALL_KICK
    };
    struct SpecialMoveInput {
        std::vector<SpecialMoveDirection> command;
        AttackButton requiredAttack;
    };
    struct SpecialSkillAnimation {
        std::unordered_map<Keys, std::vector<int>> frames;
        std::unordered_map<Keys, velocity> velocitys;
        std::unordered_map<Keys, velocity> initialvelocitys;
    };
    struct AttackData {
        std::unordered_map<Keys, HitStrength> HitStrength;
        std::unordered_map<Keys, float> attack;
    };
    struct SpecialSkillData {
        std::unordered_map<FighterState, SpecialSkillAnimation> animationData;
        std::unordered_map<FighterState, SpecialMoveInput> SkillCommand;
        std::unordered_map<FighterState, AttackData> attackdata;
    };
    struct SpecificStates {
        std::unordered_set<FighterState> borderCheckStates;
        std::unordered_set<FighterState> CrouchAttackStates;
        std::unordered_set<FighterState> HurtStates;
        std::unordered_set<FighterState> SpecialStates;
        std::unordered_set<FighterState> IdleStates;
        std::unordered_set<FighterState> BlockStates;
        std::unordered_set<FighterState> InvincibleForFlyObj;
    };
}

#endif //FIGHTERINFO_HPP