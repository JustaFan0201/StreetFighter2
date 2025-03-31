//
// Created by asus on 2025/2/27.
//

#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>

#include "Core/Context.hpp"
#include "Util/BGM.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"
#include "Util/Time.hpp"
#include "Util/SFX.hpp"

#include "Others/FighterInfo.hpp"
#include "Others/Controller.hpp"
#include "AnimationSpace.hpp"
#include "ImageSpace.hpp"
#include "Word.hpp"

namespace Util {
    class Fighter : public std::enable_shared_from_this<Fighter>{
    public:

        Fighter(std::string name,velocity velocity): m_name(name),velocity(velocity){}
        virtual ~Fighter() = default;

        virtual void IdleStateEnter();
        virtual void IdleStateUpload();

        virtual void WalkStateEnter();
        virtual void ForwardStateUpload();
        virtual void BackwardStateUpload();

        virtual void JumpStateEnter();
        virtual void JumpStateUpload();

        virtual void CrouchdownEnter();
        virtual void CrouchdownUpload();

        virtual void AttackStateEnter();
        virtual void LPStateUpload();
        virtual void MPStateUpload();
        virtual void HPStateUpload();
        virtual void LKStateUpload();
        virtual void MKStateUpload();
        virtual void HKStateUpload();

        virtual void HurtStateEnter();
        virtual void HurtStateUpload();

        virtual void BlockStateEnter();
        virtual void BlockStateUpload();

        virtual void LoadAnimations(){}
        virtual void LoadOffsetVelocity(){}
        virtual void LoadAllBox(){}
        virtual void LoadAttackSound(){}
        virtual void LoadAttackAndType();

        void SetAnimation(FighterState action,std::vector<int> intervals,std::vector<glm::vec2> offsets);
        void SetEnemy(std::shared_ptr<Fighter> enemy){this->enemy=enemy;}

        std::string GetFace() const { return face; }
        std::string GetNameTag() const { return nametag; }
        std::string GetCountry() const { return country; }
        Transform GetCountryPosition() const { return country_position; }
        std::vector<std::string> GetStageBackground() { return stage_background; }
        std::string GetName() const { return m_name; }
        std::shared_ptr<BGM> GetBGM() { return m_BGM; }
        float GetHP() const{return hp;}
        void GetAttack(){hp-=attacks.count(enemy->currentState)?attacks[enemy->currentState]:0;}
        HitStrength GetHitStrength(){return hitstrength.count(currentState)?hitstrength[currentState]:HitStrength::Null;}
        FighterState GetHitState(HitStrength Strength,HitLocation Location);

        int GetDirection();
        bool GetAnimationIsEnd() const {return ActionNow->IsAnimationEnds();}
        bool GetCharacterIsOnFloor() const {return ActionNow->m_Transform.translation.y==FloorOfCharacter;}
        glm::vec2 GetCurrentPosition() const {return ActionNow->m_Transform.translation;}
        glm::vec2 GetCurrentOffsetPosition() {return ActionNow->m_Transform.translation+GetCurrentOffsets()[0]*ActionNow->GetTransform().scale;}
        std::vector<glm::vec2> GetCurrentOffsets(){return offset.count(currentState) ? offset[currentState]:offset[FighterState::Idle];}
        glm::vec2 GetCurrentPushbox() {return boxes.pushbox.size.count(currentState) ? boxes.pushbox.size[currentState] : boxes.pushbox.size[FighterState::Idle];}
        glm::vec2 GetCurrentPushboxOffset(){return (boxes.pushbox.offset.count(currentState) ? boxes.pushbox.offset[currentState] : boxes.pushbox.offset[FighterState::Idle])*ActionNow->GetTransform().scale;}

        std::array<glm::vec2, 3> GetCurrentHurtboxSize() {
            return {
                boxes.hurtbox.head.size.count(currentState) ?
                boxes.hurtbox.head.size[currentState] :
                boxes.hurtbox.head.size[FighterState::Idle],

                boxes.hurtbox.body.size.count(currentState) ?
                boxes.hurtbox.body.size[currentState] :
                boxes.hurtbox.body.size[FighterState::Idle],

                boxes.hurtbox.leg.size.count(currentState) ?
                boxes.hurtbox.leg.size[currentState] :
                boxes.hurtbox.leg.size[FighterState::Idle]
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

        void AttackHit(HitStrength Strength,HitLocation Location);

        void BackgroundInit(int picture_number);
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        void InitPosition(glm::vec2 position,int side,int Whichplayer);
        void StateInit();
        void debugInit();

        void ResetVelocity(){velocity={0,0};}
        void ChangeState(FighterState newState);
        void BorderDetection(int MaxWidth);
        void ReSize();
        void UploadStateAndNewXY();

        void Upload(std::shared_ptr<Core::Context> context);
        void DrawCharacter();

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
        std::shared_ptr<Controller> controller=std::make_shared<Controller>(1);

        bool AttackStruck=false;
        float hp=100;
        int direction;
        float FloorOfCharacter;
        float Gravity=-4800;
        float Friction=800;
        velocity velocity;
        Initialvelocity Initialvelocity;
        Boxes boxes;
        //debugTest
        std::shared_ptr<AnimationSpace> pushboxPicture=nullptr;
        std::shared_ptr<AnimationSpace> headPicture=nullptr;
        std::shared_ptr<AnimationSpace> bodyPicture=nullptr;
        std::shared_ptr<AnimationSpace> legPicture=nullptr;
        std::shared_ptr<AnimationSpace> hitPicture=nullptr;
        glm::vec2 mouse;
        std::vector<glm::vec2> Allofmouse;
    };
}
#endif //FIGHTER_HPP