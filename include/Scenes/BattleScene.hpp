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

namespace Util {
    class BattleScene : public Scene{
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<Controller> playerController=std::make_shared<Controller>(PlayerType::Null);
        std::shared_ptr<Controller> enemyController=std::make_shared<Controller>(PlayerType::Null);
        std::shared_ptr<Camera> camera=std::make_shared<Camera>();
        std::shared_ptr<UI> bloodstick=std::make_shared<UI>();
        std::vector<std::shared_ptr<FlyingObect>> PlayerFlyingObjects;
        std::vector<std::shared_ptr<FlyingObect>> EnemyFlyingObjects;
        int round=1;
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy):
        player(player), enemy(enemy){}

        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
        void addEntities(FlyingObjectType type, std::shared_ptr<Fighter> sender, Keys strength);
        void UpdateFlyingObjects(std::vector<std::shared_ptr<FlyingObect>>& flyingObjects,glm::vec2 cameraOffset);
    };
}

#endif //BATTLESCENE_HPP