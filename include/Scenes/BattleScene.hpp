//
// Created by Gs0n 25-3-2.
//

#ifndef BATTLESCENE_HPP
#define BATTLESCENE_HPP

#include "Scene.hpp"
#include "Others/FighterInfo.hpp"
#include "Others/Camera.hpp"
#include "Others/Bloodstick.hpp"
#include "FlyingObject/FlyingObject.hpp"
#include "FlyingObject/FireBall.hpp"

namespace Util {
    class BattleScene : public Scene{
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Bloodstick> bloodstick;
        std::vector<std::shared_ptr<FlyingObect>> PlayerFlyingObjects;
        std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects;
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy)
            : player(player), enemy(enemy), camera(std::make_shared<Camera>()), bloodstick(std::make_shared<Bloodstick>()) {}

        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
        void addEntities(FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength);
        void UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObect>>& flyingObjects);
    };
}

#endif //BATTLESCENE_HPP