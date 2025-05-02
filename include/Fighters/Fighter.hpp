//
// Created by asus on 2025/2/27.
//

#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include <memory>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "Core/Context.hpp"
#include "Util/BGM.hpp"
#include "Util/Input.hpp"
#include "Util/Transform.hpp"
#include "Util/Time.hpp"
#include "Util/SFX.hpp"

#include "Others/FighterInfo.hpp"
#include "Others/Controller.hpp"
#include "AnimationSpace.hpp"
#include "ImageSpace.hpp"

#include "Others/FlyingObjectInfo.hpp"

namespace Util {
    class Fighter : public std::enable_shared_from_this<Fighter>{
    public:

        Fighter(std::string name): m_name(name){velocity={0,0};}
        virtual ~Fighter() = default;

        virtual void IdleStateEnter();
        virtual void IdleStateUpload();

        virtual void WalkStateEnter();
        virtual void ForwardStateUpload();
        virtual void BackwardStateUpload();

        virtual void JumpStateEnter();
        virtual void JumpStateUpload();

        virtual void CrouchEnter();
        virtual void CrouchUpload();
        virtual void CrouchDownUpload();
        virtual void CrouchUpUpload();

        virtual void AttackStateEnter();
        virtual void AttackStateUpload();

        virtual void HurtStateEnter();
        virtual void HurtStateUpload();

        virtual void BlockStateEnter();
        virtual void BlockStateUpload();

        virtual void WinStateEnter();
        virtual void WinStartStateUpload();
        virtual void WinStateUpload();

        virtual void LossStateEnter();
        virtual void LossStateUpload();

        virtual void LoadAnimations(){}
        virtual void LoadOffsetVelocity(){}
        void LoadCommonVelocities();
        virtual void LoadAllBox(){}
        virtual void LoadAttackSound();
        virtual void LoadAttackAndType();
        void LoadCurrentSpecialMove(Keys ButtonType);

        void SetAnimation(FighterState action,std::vector<int> intervals,std::vector<glm::vec2> offsets);
        void SetEnemy(std::shared_ptr<Fighter> enemy){this->enemy=enemy;}
        void SetEntityAdder(std::function<void(FlyingObjectType type, std::shared_ptr<Fighter>, Keys)> func) {addEntityFunc = func;}

        std::string GetFace() const { return face; }
        std::string GetNameTag() const { return nametag; }
        std::string GetCountry() const { return country; }
        Transform GetCountryPosition() const { return country_position; }
        std::vector<std::string> GetStageBackground() { return stage_background; }
        std::string GetName() const { return m_name; }
        std::shared_ptr<BGM> GetBGM() { return m_BGM; }
        std::unordered_map<FighterState, std::shared_ptr<SFX>> GetSFX() { return soundeffect; }

        float GetHP() const{return hp;}
        std::shared_ptr<Fighter> GetEnemy(){return enemy;}
        float GetAttackNum(){return attacks.count(currentState)?attacks[currentState]:0;}
        void GetAttack(float dmg){hp-=dmg;}
        int GetDirection() const{return direction;}
        glm::vec2 GetVelocity() const{return velocity;}
        glm::vec2 GetInitialvelocity() {
            return glm::vec2{
                Initialvelocity.x.count(currentState) ?
                 Initialvelocity.x[currentState] : 0,

                Initialvelocity.y.count(currentState) ?
                 Initialvelocity.y[currentState] : 0,
            };
        }
        HitStrength GetHitStrength(){return hitstrength.count(currentState)?hitstrength[currentState]:HitStrength::Null;}
        FighterState GetBeHitState(HitStrength Strength,HitLocation Location);
        FighterState GetBlockState();
        FighterState GetCurrentState() const {return currentState;};
        SpecificStates GetSpecificState(){return SpecificStates;};

        float GetHalfFighterWidth(){return std::abs(ActionNow->GetCustomSize().x) / 2.0f;}
        int GetNewDirection();
        bool GetAnimationIsEnd() const {return ActionNow->IsAnimationEnds();}
        bool GetCharacterIsOnFloor() const {return ActionNow->m_Transform.translation.y==FloorOfCharacter;}
        bool GetCharacterIsInBorder()  {
            float halfFighterWidth = GetHalfFighterWidth();
            float worldX = GetCurrentPosition().x;
            if (worldX - MaxCameraOffsetX > MaxWidth - halfFighterWidth || worldX + MaxCameraOffsetX < -MaxWidth + halfFighterWidth) {
                return true;
            }
            return false;
        }
        glm::vec2 GetCurrentPosition() const {return ActionNow->m_Transform.translation;}
        glm::vec2 GetCurrentOffsetPosition() {return ActionNow->m_Transform.translation+GetCurrentOffsets()[0]*ActionNow->GetTransform().scale;}
        std::vector<glm::vec2> GetCurrentOffsets(){return offset.count(currentState) ? offset[currentState]:offset[FighterState::Idle];}
        glm::vec2 GetCurrentPushbox() {
            if(SpecificStates.CrouchAttackStates.count(currentState)) {
                return boxes.pushbox.size.count(currentState) ? boxes.pushbox.size[currentState] : boxes.pushbox.size[FighterState::Crouch];
            }
            return boxes.pushbox.size.count(currentState) ? boxes.pushbox.size[currentState] : boxes.pushbox.size[FighterState::Idle];
        }
        glm::vec2 GetCurrentPushboxOffset() {
            if(SpecificStates.CrouchAttackStates.count(currentState)) {
                return (boxes.pushbox.offset.count(currentState) ? boxes.pushbox.offset[currentState] : boxes.pushbox.offset[FighterState::Crouch])*ActionNow->GetTransform().scale;
            }
            return (boxes.pushbox.offset.count(currentState) ? boxes.pushbox.offset[currentState] : boxes.pushbox.offset[FighterState::Idle])*ActionNow->GetTransform().scale;
        }

        std::array<glm::vec2, 3> GetCurrentHurtboxSize() {
            return {
                boxes.hurtbox.head.size.count(currentState) ?
                boxes.hurtbox.head.size[currentState][ActionNow->GetCurrentFrameIndex()] :
                boxes.hurtbox.head.size[FighterState::Idle][0],

                boxes.hurtbox.body.size.count(currentState) ?
                boxes.hurtbox.body.size[currentState][ActionNow->GetCurrentFrameIndex()] :
                boxes.hurtbox.body.size[FighterState::Idle][0],

                boxes.hurtbox.leg.size.count(currentState) ?
                boxes.hurtbox.leg.size[currentState][ActionNow->GetCurrentFrameIndex()] :
                boxes.hurtbox.leg.size[FighterState::Idle][0]
            };
        }//0 head 1 body 2 leg
        std::array<glm::vec2, 3> GetCurrentHurtboxOffset() {
            return {
                (boxes.hurtbox.head.offset.count(currentState) ?
                 boxes.hurtbox.head.offset[currentState][ActionNow->GetCurrentFrameIndex()] :
                 boxes.hurtbox.head.offset[FighterState::Idle][0])* ActionNow->GetTransform().scale,

                (boxes.hurtbox.body.offset.count(currentState) ?
                 boxes.hurtbox.body.offset[currentState][ActionNow->GetCurrentFrameIndex()] :
                 boxes.hurtbox.body.offset[FighterState::Idle][0]) * ActionNow->GetTransform().scale,

                (boxes.hurtbox.leg.offset.count(currentState) ?
                 boxes.hurtbox.leg.offset[currentState][ActionNow->GetCurrentFrameIndex()] :
                 boxes.hurtbox.leg.offset[FighterState::Idle][0])* ActionNow->GetTransform().scale
            };
        }

        glm::vec2 GetCurrentHitbox() {
            return boxes.hitbox.size.count(currentState) ?
                   boxes.hitbox.size[currentState] : glm::vec2{0,0};
        }
        glm::vec2 GetCurrentHitboxOffset() {
            if (!boxes.hitbox.offset.count(currentState)) {
                return {-1, -1};
            }
            if(boxes.hitbox.offset[currentState][ActionNow->GetCurrentFrameIndex()]==glm::vec2{-1,-1}) {
                return {-1,-1};
            }
            return boxes.hitbox.offset[currentState][ActionNow->GetCurrentFrameIndex()]*ActionNow->GetTransform().scale;
        }

        bool PushboxIsCollidedEnemy() {
            return RectangleOverlap(
                GetCurrentPosition()+GetCurrentPushboxOffset(),
                GetCurrentPushbox(),
                enemy->GetCurrentPosition()+enemy->GetCurrentPushboxOffset(),
                enemy->GetCurrentPushbox());
        }
        void HitboxIsCollidedEnemy();

        void AttackHit(HitStrength Strength,HitLocation Location,float dmg);
        void AttackBlock();
        bool IsBlocking();

        void ClearButtonType(){ButtonType=Keys::Null;}
        void AddFlyingObject(FlyingObjectType object, Keys strength) {
            if (ButtonType!=Keys::Null) {addEntityFunc(object, shared_from_this(), strength);}}
        void PlayCurrentSound() {
            if(soundeffect.count(currentState)) {
                soundeffect[currentState]->Play();
            }
        }
        void BackgroundInit(int picture_number);
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        void InitPosition(glm::vec2 position,int side,std::shared_ptr<Controller> controller,int MaxCameraOffsetX);
        void StateInit();
        void debugInit();

        void ResetVelocity(){velocity={0,0};}
        void ChangeState(FighterState newState);
        void BorderDetection(int MaxWidth,glm::vec2 cameraOffset);
        virtual void SkillDetection();
        void SkillErrorPrevent(Keys key, const std::vector<Keys>& reqType);
        void ReSize();
        void UploadStateAndNewXY();

        void Upload(std::shared_ptr<Core::Context> context,std::shared_ptr<Controller> controller,glm::vec2 cameraOffset);
        void DrawCharacter(glm::vec2 cameraOffset);

        //debugTest
        void PrintPostion();
        void PostionTester();
        void PushBoxTester();

    protected:
        std::string m_name;
        std::string face;
        std::string nametag;
        std::string country;
        Transform country_position;
        std::vector<std::string> stage_background;
        std::shared_ptr<BGM> m_BGM;
        std::unordered_map<FighterState, std::shared_ptr<SFX>> soundeffect;

        float currentAnimationIndex=0;
        FighterState currentState;

        std::unordered_map<FighterState, std::function<void()>> StateEnter;
        std::unordered_map<FighterState, std::function<void()>> StateUpload;
        std::unordered_map<FighterState, std::vector<std::string>> animations;
        std::unordered_map<FighterState, std::vector<int>> frames;
        std::unordered_map<FighterState, std::vector<glm::vec2>> offset;

        std::unordered_map<FighterState, HitStrength> hitstrength;
        std::unordered_map<FighterState, float> attacks;

        std::shared_ptr<AnimationSpace> ActionNow;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<Controller> controller=std::make_shared<Controller>(PlayerType::Null);

        Keys ButtonType=Keys::Null;
        std::function<void(FlyingObjectType type, std::shared_ptr<Fighter>, Keys)> addEntityFunc;

        bool AttackStruck=false;
        bool HitEnemy=false;
        float hp=100;
        int direction;
        float FloorOfCharacter=0;
        float Gravity=-98;
        float Friction=16;
        float MaxWidth;
        int MaxCameraOffsetX;
        float currentCameraX;

        glm::vec2 velocity;
        Initialvelocity Initialvelocity;

        Boxes boxes;
        SpecialSkillData SpecialMoveData;
        SpecificStates SpecificStates;
        //debugTest
        std::shared_ptr<AnimationSpace> pushboxPicture=nullptr;
        std::shared_ptr<AnimationSpace> headPicture=nullptr;
        std::shared_ptr<AnimationSpace> bodyPicture=nullptr;
        std::shared_ptr<AnimationSpace> legPicture=nullptr;
        std::shared_ptr<AnimationSpace> hitPicture=nullptr;
        glm::vec2 mouse;
        std::vector<glm::vec2> Allofmouse;

        bool controllerTest=true;
    };
}
#endif //FIGHTER_HPP