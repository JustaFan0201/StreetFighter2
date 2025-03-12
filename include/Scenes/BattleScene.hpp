//
// Created by Gs0n 25-3-2.
//

#ifndef BATTLESCENE_HPP
#define BATTLESCENE_HPP

#include "Scene.hpp"
#include "Others/FighterInfo.hpp"
#include "Others/Camera.hpp"
#include "Others/Bloodstick.hpp"

namespace Util {
    class BattleScene : public Scene{
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Bloodstick> bloodstick;
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy)
            : player(player), enemy(enemy), camera(std::make_shared<Camera>()), bloodstick(std::make_shared<Bloodstick>()) {}
        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
    };
}

#endif //BATTLESCENE_HPP