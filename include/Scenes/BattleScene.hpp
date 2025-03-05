//
// Created by Gson 25-3-2.
//

#ifndef BATTLESCENE_HPP
#define BATTLESCENE_HPP

#include "Scene.hpp"

namespace Util {
    class BattleScene : public Scene {
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        int maxOffsetX, minOffsetX;
        struct { int x, y; } cameraPos = {0, 0};
    public:
        BattleScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy):player(player),enemy(enemy){}
        void Init() override;
        void Update() override;
        void Render() override;
    };
}

#endif //BATTLESCENE_HPP
