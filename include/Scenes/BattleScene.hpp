//
// Created by Gson 25-3-2.
//

#ifndef BATTLESCENE_HPP
#define BATTLESCENE_HPP

#include "Scene.hpp"
#include "Camera.hpp"

namespace Util {
    class BattleScene : public Scene{
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        std::shared_ptr<Camera> camera;
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy)
            : player(player), enemy(enemy), camera(std::make_shared<Camera>()) {}
        void Init() override;
        void Update() override;
        void Render() override;
    };
}

#endif //BATTLESCENE_HPP