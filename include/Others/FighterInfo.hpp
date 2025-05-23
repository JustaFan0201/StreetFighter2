//
// Created by asus on 2025/3/12.
//

#ifndef FIGHTERINFO_HPP
#define FIGHTERINFO_HPP
#include <random>
namespace Util {
    enum class FinalResult {
        Null,
        Tie,
        Player1Win,
        Player2Win
    };
    enum class FighterList {
        Ryu=0,
        Honda=1,
        Blanka=2,
        Guile=3,
        Ken=4,
        Chunli=5,
        Zangief=6,
        Dhalsim=7
    };
    constexpr float StageFloor = -310.0f;
    enum class FighterDirection {
        Left  = 1,
        Right = -1
    };
    enum class FighterState {
        Null,
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
        JumpAttackEnd,
        Special_1,
        Special_2,
        Special_3,
        SpecialRecovery_1,
        SpecialRecovery_2,
        SpecialRecovery_3,
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
        TimeOverLoss,
        DefeatedLoss
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
    enum class AttackType {
        Null=-1,
        Upper = 0,
        Lower = 1,
        Middle = 2
    };
    enum class BeHitType {
        Null=-1,
        Block = 0,
        Hit = 1
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
    inline float GetRandomNum(float min,float max){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }
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
        HK,
        ENTER
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
    enum class CommandType {
        Null,
        Command,
        Pressed
    };
    struct ButtonList {
        static inline const std::vector<Keys> punch{Keys::LP, Keys::MP, Keys::HP};
        static inline const std::vector<Keys> kick{Keys::LK, Keys::MK, Keys::HK};
    };
    struct SpecialMoveInput {
        std::vector<SpecialMoveDirection> command;
        AttackButton requiredAttack;
        CommandType commandtype;
        std::unordered_map<Keys, float> chargetime;
    };
    struct SpecialSkillAnimation {
        std::unordered_map<Keys, std::vector<int>> frames;
        std::unordered_map<Keys, glm::vec2> velocitys;
        std::unordered_map<Keys, glm::vec2> initialvelocitys;
    };
    struct AttackData {
        std::unordered_map<Keys, HitStrength> HitStrength;
        std::unordered_map<Keys, float> attack;
    };
    struct SoundData {
        std::unordered_map<Keys, std::shared_ptr<SFX>> sound;
    };
    struct SpecialSkillData {
        std::unordered_map<FighterState, SpecialSkillAnimation> animationData;
        std::unordered_map<FighterState, SpecialMoveInput> SkillCommand;
        std::unordered_map<FighterState, AttackData> attackdata;
        std::unordered_map<FighterState, SoundData> sounddata;
    };
    struct SpecificStates {
        std::unordered_set<FighterState> borderCheckStates;
        std::unordered_set<FighterState> CrouchAttackStates;
        std::unordered_set<FighterState> HurtStates;
        std::unordered_set<FighterState> SpecialStates;
        std::unordered_set<FighterState> IdleStates;
        std::unordered_set<FighterState> StandStates;
        std::unordered_set<FighterState> CrouchStates;
        std::unordered_set<FighterState> BlockStates;
        std::unordered_set<FighterState> CanBlockStates;
        std::unordered_set<FighterState> InvincibleForFlyObj;
        std::unordered_set<FighterState> Invincible;
    };
}

#endif //FIGHTERINFO_HPP