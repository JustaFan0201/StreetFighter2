//
// Created by Gs0n 25-3-2.
//

#ifndef BATTLESCENE_HPP
#define BATTLESCENE_HPP

#include "Scene.hpp"
#include "Others/FighterInfo.hpp"
#include "Others/Camera.hpp"
#include "Others/UI.hpp"
#include "FlyingObject/FlyingObject.hpp"
#include "FlyingObject/FireBall.hpp"
#include "FlyingObject/SonicBoom.hpp"
#include "FlyingObject/YogaFire.hpp"

namespace Util {
    enum class DefeatedType {
        Null,
        Player,
        Enemy,
        Both
    };
    enum class LossType {
        Null,
        NoHP,
        TimeOver
    };
    class BattleScene : public Scene{
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<Controller> playerController=std::make_shared<Controller>(PlayerType::Null);
        std::shared_ptr<Controller> enemyController=std::make_shared<Controller>(PlayerType::Null);
        std::shared_ptr<Camera> camera=std::make_shared<Camera>();
        std::shared_ptr<UI> ui=std::make_shared<UI>();
        std::vector<std::shared_ptr<FlyingObject>> PlayerFlyingObjects;
        std::vector<std::shared_ptr<FlyingObject>> EnemyFlyingObjects;
        int round=1;
        int PlayerWinCounter=0;
        int EnemyWinCounter=0;
        DefeatedType defeatedType=DefeatedType::Null;
        LossType lossType=LossType::Null;

        std::pmr::unordered_map<FlyingObjectType, std::function<std::shared_ptr<FlyingObject>()>> flyingObjFactory;
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy):
        player(player), enemy(enemy) {
            flyingObjFactory[FlyingObjectType::Null] = []() { return nullptr; };
            flyingObjFactory[FlyingObjectType::FireBall] = []() {return std::make_shared<FireBall>();};
            flyingObjFactory[FlyingObjectType::SonicBoom] = []() {return std::make_shared<SonicBoom>();};
            flyingObjFactory[FlyingObjectType::YogaFire] = []() {return std::make_shared<YogaFire>();};
        }

        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
        void addEntities(FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength);
        void UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObject>>& flyingObjects,glm::vec2 cameraOffset);
        void RoundStart(std::shared_ptr<Core::Context> context);
        float GetPassedTime(){return static_cast<int>(Time::GetElapsedTimeMs() - start_time);}
        void ControllerState();
        void LossJudge();
        void LossStateForFighter();
        void WinStateForFighter();
        void EndForRound(std::shared_ptr<Core::Context> context);
        void JudgeBattleEnd();
    };
}
#endif //BATTLESCENE_HPP