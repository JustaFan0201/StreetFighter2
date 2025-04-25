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
        virtual void Init(std::shared_ptr<Fighter> fighter,Keys Strength,std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects)=0;
        virtual void Update(std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects,glm::vec2 cameraOffset);
        virtual void Draw(glm::vec2 cameraOffset);

        void Movement(glm::vec2 cameraOffset);
        FlyingObjectCollidedState IsCollidedEnemy();
        FlyingObjectCollidedState IsCollidedEntity();

        bool IsEnd() const{return ObjectIsEnd;}
        std::string GetName(){return Name;};

        glm::vec2 GetCurrentPosition() const {return animationNow->m_Transform.translation;}
        glm::vec2 GetCurrentHitbox() {
            return hitbox.size.count(currentState) ?
                   hitbox.size[currentState] : glm::vec2{0,0};
        }

        void ChangeState(FlyingObjectState newState);
        bool IsAnimationEnd() const {return animationNow->IsAnimationEnds();}
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        void SetAnimation(FlyingObjectState action, int duration);
    protected:
        std::string Name;
        FlyingObjectType Type;
        int direction;
        glm::vec2 velocity;
        Keys Strength=Keys::Null;

        FlyingObjectState currentState;
        std::unordered_map<Keys, float> FireBallVelocity;
        std::unordered_map<Keys, float> FireBallDmg;
        std::unordered_map<FlyingObjectState, std::vector<std::string>> animations;
        FlyingObjectBox hitbox;
        bool ObjectIsEnd=false;

        std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects;
        std::shared_ptr<Fighter> fighter;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<AnimationSpace> animationNow;
    };
}
#endif //FLYINGOBJECT_HPP
