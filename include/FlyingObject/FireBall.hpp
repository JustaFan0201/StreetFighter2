//
// Created by FanFan on 2025/4/5.
//

#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "FlyingObject/FlyingObject.hpp"

namespace Util {
    class FireBall:public FlyingObect {
    public:
        FireBall();
        void Init(std::shared_ptr<Fighter> fighter,Keys Strength)override;
        void Update()override;
        void Draw()override;
    };
}
#endif //FIREBALL_HPP
