//
// Created by Gson 25-3-2.
//

#ifndef BATTLESCENE_HPP
#define BATTLESCENE_HPP

#include "Scene.hpp"

namespace Util {
    class BattleScene : public Scene {
    private:
        std::shared_ptr<ImageSpace> background;  // 背景圖片
    public:
        BattleScene();
        void Init() override;
        void Update() override;
        void Render() override;
    };
}

#endif //BATTLESCENE_HPP
