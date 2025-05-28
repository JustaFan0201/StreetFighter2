//
// Created by asus on 2025/5/29.
//

#ifndef VEGA_HPP
#define VEGA_HPP
#include "Fighter.hpp"

namespace Util {
    class Vega : public Fighter  {
    public:
        Vega();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
        void LoadSpecialMove()override;
    };
}
#endif //VEGA_HPP
