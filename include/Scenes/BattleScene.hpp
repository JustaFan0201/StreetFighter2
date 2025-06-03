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

#include "Effect/Effect.hpp"
#include "Effect/Hit_L.hpp"
#include "Effect/Hit_M.hpp"
#include "Effect/Hit_H.hpp"
#include "Effect/Block_L.hpp"
#include "Effect/Block_M.hpp"
#include "Effect/Block_H.hpp"
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
        std::vector<std::shared_ptr<Effect>> Effects;
        int round=1;
        int PlayerWinCounter=0;
        int EnemyWinCounter=0;
        DefeatedType defeatedType=DefeatedType::Null;
        LossType lossType=LossType::Null;
        FinalResult finalresult=FinalResult::Null;

        std::pmr::unordered_map<FlyingObjectType, std::function<std::shared_ptr<FlyingObject>()>> flyingObjFactory;
        std::pmr::unordered_map<HitStrength, std::function<std::shared_ptr<Effect>()>> HitEffectFactory;
        std::pmr::unordered_map<HitStrength, std::function<std::shared_ptr<Effect>()>> BlockEffectFactory;
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy):
        player(player), enemy(enemy) {
            flyingObjFactory[FlyingObjectType::Null] = []() { return nullptr; };
            flyingObjFactory[FlyingObjectType::FireBall] = []() {return std::make_shared<FireBall>();};
            flyingObjFactory[FlyingObjectType::SonicBoom] = []() {return std::make_shared<SonicBoom>();};
            flyingObjFactory[FlyingObjectType::YogaFire] = []() {return std::make_shared<YogaFire>();};

            HitEffectFactory[HitStrength::L] = []() {return std::make_shared<Hit_L>();};
            HitEffectFactory[HitStrength::M] = []() {return std::make_shared<Hit_M>();};
            HitEffectFactory[HitStrength::H] = []() {return std::make_shared<Hit_H>();};

            BlockEffectFactory[HitStrength::L] = []() {return std::make_shared<Block_L>();};
            BlockEffectFactory[HitStrength::M] = []() {return std::make_shared<Block_M>();};
            BlockEffectFactory[HitStrength::H] = []() {return std::make_shared<Block_H>();};
        }

        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
        void InitPlayerSetting() ;
        void InitControllerSetting() ;
        void addEntities(FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength);
        void addEffects(HitStrength strength,BeHitType behittype, glm::vec2 position);
        void UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObject>>& flyingObjects,glm::vec2 cameraOffset);
        void UpdateEffects();
        void RoundStart(std::shared_ptr<Core::Context> context);
        void ControllerState();
        void LossJudge();
        void LossStateForFighter();
        void WinStateForFighter();
        void EndForRound(std::shared_ptr<Core::Context> context);
        void JudgeBattleEnd();
        FinalResult GetFinalResult() const {return finalresult;}
        void LetSomeoneLoss() const;
    };
}
#endif //BATTLESCENE_HPP