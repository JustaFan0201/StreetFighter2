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
#include <any>
#include <functional>

#include "Core/Context.hpp"
#include "Util/BGM.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"
#include "Util/Time.hpp"
#include "Util/SFX.hpp"

#include "Others/FighterInfo.hpp"
#include "AnimationSpace.hpp"
#include "ImageSpace.hpp"
#include "Word.hpp"

namespace Util {
    class Fighter : public std::enable_shared_from_this<Fighter>{
    public:

        Fighter(const std::string& name,velocity velocity): m_name(name),velocity(velocity) {}
        virtual ~Fighter() = default;

        virtual void IdleStateEnter(){}
        virtual void IdleStateUpload(){}

        virtual void WalkStateEnter(){}
        virtual void WalkStateUpload(){}
        virtual void JumpStateEnter(){}
        virtual void JumpStateUpload(){}

        virtual void LPStateEnter(){}
        virtual void LPStateUpload(){}
        virtual void MPStateEnter(){}
        virtual void MPStateUpload(){}

        virtual void LKStateEnter(){}
        virtual void LKStateUpload(){}
        virtual void MKStateEnter(){}
        virtual void MKStateUpload(){}
        virtual void HKStateEnter(){}
        virtual void HKStateUpload(){}

        virtual void LoadAnimations(){}
        virtual void LoadOffsetVelocity(){}

        void SetAnimation(FighterState action,std::vector<int> intervals,std::vector<glm::vec2> offsets);

        std::string GetFace() const { return face; }
        std::string GetNameTag() const { return nametag; }
        std::string GetCountry() const { return country; }
        Transform GetCountryPosition() const { return country_position; }
        std::vector<std::string> GetStageBackground() { return stage_background; }
        std::string GetName() const { return m_name; }
        std::shared_ptr<BGM> GetBGM() { return m_BGM; }
        bool GetAnimationIsEnd() const {return ActionNow->IsAnimationEnds();}
        bool GetCharacterIsOnFloor() const {return ActionNow->m_Transform.translation.y==StageFloor;}

        void BackgroundInit(int picture_number);
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        void InitPosition(glm::vec2 position,int side);
        void StateInit();

        void ChangeState(FighterState newState);
        void BorderDection(int MaxWidth);
        void ReSize();
        void Upload(std::shared_ptr<Core::Context> context);
        void DrawCharacter();
    protected:
        std::string m_name;
        std::string face;
        std::string nametag;
        std::string country;
        Transform country_position;
        std::vector<std::string> stage_background;

        FighterState currentState;
        std::unordered_map<FighterState, std::function<void()>> StateEnter;
        std::unordered_map<FighterState, std::function<void()>> StateUpload;
        std::unordered_map<FighterState, std::vector<std::string>> animations;
        std::unordered_map<FighterState, std::vector<int>> frames;
        std::unordered_map<FighterState, std::vector<glm::vec2>> offset;

        std::shared_ptr<AnimationSpace> ActionNow;
        std::shared_ptr<BGM> m_BGM;

        float Gravity=-5200;
        velocity velocity;
        Initialvelocity Initialvelocity;
        int direction;
    };
}
#endif //FIGHTER_HPP
