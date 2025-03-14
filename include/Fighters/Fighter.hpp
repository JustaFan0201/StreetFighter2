//
// Created by asus on 2025/2/27.
//

#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
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
        class FighterState {
        public:
            virtual ~FighterState() = default;
            virtual void Enter(std::shared_ptr<Fighter> fighter) = 0;
            virtual void Update(std::shared_ptr<Fighter> fighter) = 0;
        };

        class IdleState : public FighterState {
        public:
            void Enter(std::shared_ptr<Fighter> fighter) override;
            void Update(std::shared_ptr<Fighter> fighter) override;
        };

        class ForwardState : public FighterState {
        public:
            void Enter(std::shared_ptr<Fighter> fighter) override;
            void Update(std::shared_ptr<Fighter> fighter) override;
        };

        class BackState : public FighterState {
        public:
            void Enter(std::shared_ptr<Fighter> fighter) override;
            void Update(std::shared_ptr<Fighter> fighter) override;
        };

        class LPState : public FighterState {
        public:
            void Enter(std::shared_ptr<Fighter> fighter) override;
            void Update(std::shared_ptr<Fighter> fighter) override;
        };

        class MPState : public FighterState {
        public:
            void Enter(std::shared_ptr<Fighter> fighter) override;
            void Update(std::shared_ptr<Fighter> fighter) override;
        };

        Fighter(const std::string& name,int velocity): m_name(name),velocity(velocity) {}
        virtual ~Fighter() = default;
        std::string GetFace() const { return face; }
        std::string GetNameTag() const { return nametag; }
        std::string GetCountry() const { return country; }
        Transform GetCountryPosition() const { return country_position; }
        std::vector<std::string> GetStageBackground() { return stage_background; }
        std::string GetName() const { return m_name; }
        std::shared_ptr<BGM> GetBGM() { return m_BGM; }

        void BackgroundInit(int picture_number);
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        //輸入frame (num)圖數量 圖放在對應角色資料夾 Action輸入資料夾名稱
        void InitPosition(glm::vec2 position,int side,float Floor);
        void BorderDection(int MaxWidth);

        void ChangeState(std::shared_ptr<FighterState> newState);
        void ReSize();
        void Upload(std::shared_ptr<Core::Context> context);
        void DrawCharacter();
    protected:
        std::string face;
        std::string nametag;
        std::string country;
        Transform country_position;
        std::vector<std::string> stage_background;

        std::vector<std::string> Idle;
        std::vector<std::string> Back;
        std::vector<std::string> Forward;
        std::vector<std::string> LP;
        std::vector<std::string> MP;
        std::shared_ptr<FighterState> currentState=std::make_shared<IdleState>();

        std::shared_ptr<AnimationSpace> ActionNow;
        std::shared_ptr<BGM> m_BGM;
        std::string m_name;
        int velocity = 0;
        int direction;
        float recoveryTime = 0.0f;
    };
}
#endif //FIGHTER_HPP
