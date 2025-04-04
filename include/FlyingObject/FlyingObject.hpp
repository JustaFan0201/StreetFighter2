//
// Created by FanFan on 2025/4/5.
//

#ifndef FLYINGOBJECT_HPP
#define FLYINGOBJECT_HPP
#include "Fighters/Fighter.hpp"
#include "Others/FlyingObjectInfo.hpp"
#include "Fighters/Ryu.hpp"
#include "Fighters/Guile.hpp"
#include "Fighters/Zangief.hpp"
#include "Fighters/Chunli.hpp"
#include "Fighters/Dhalsim.hpp"
#include "Fighters/Blanka.hpp"
#include "Fighters/Ken.hpp"
#include "Fighters/Honda.hpp"

namespace Util {
    class FlyingObect {
    public:
        FlyingObect(std::string name): Name(name){}
        virtual ~FlyingObect() = default;
        virtual void Init(std::shared_ptr<Fighter> fighter,Keys Strength){}
        virtual void Update(){}
        virtual void Draw(){}

        void Movement();
        std::string GetName(){return Name;};
        bool IsEnd() const{return ObjectIsEnd;}
        std::vector<glm::vec2> GetCurrentOffsets(){return offset.count(currentState) ? offset[currentState]:offset[FlyingObjectState::Start];}
        glm::vec2 GetCurrentHitbox() {
            return hitbox.size.count(currentState) ?
                   hitbox.size[currentState] : glm::vec2{0,0};
        }
        glm::vec2 GetCurrentHitboxOffset() {
            if (!hitbox.offset.count(currentState)) {
                return {-1, -1};
            }
            if(hitbox.offset[currentState][animationNow->GetCurrentFrameIndex()]==glm::vec2{-1,-1}) {
                return {-1,-1};
            }
            return hitbox.offset[currentState][animationNow->GetCurrentFrameIndex()]*animationNow->GetTransform().scale;
        }

        void ChangeState(FlyingObjectState newState);
        bool IsAnimationEnd() const {return animationNow->IsAnimationEnds();}
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        void SetAnimation(FlyingObjectState action,std::vector<int> intervals,std::vector<glm::vec2> offsets);
    protected:
        std::string Name;
        FlyingObjectType Type;
        int direction;
        velocity velocity;

        FlyingObjectState currentState;
        std::unordered_map<Keys, float> FireBallVelocity;
        std::unordered_map<FlyingObjectState, std::vector<std::string>> animations;
        std::unordered_map<FlyingObjectState, std::vector<int>> frames;
        std::unordered_map<FlyingObjectState, std::vector<glm::vec2>> offset;
        FlyingObjectBox hitbox;
        bool ObjectIsEnd=false;

        std::shared_ptr<Fighter> fighter;
        std::shared_ptr<AnimationSpace> animationNow;
    };
}
#endif //FLYINGOBJECT_HPP
