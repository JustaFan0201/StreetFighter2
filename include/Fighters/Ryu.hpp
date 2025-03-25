//
// Created by asus on 2025/2/27.
//

#ifndef RYU_HPP
#define RYU_HPP

#include "Fighter.hpp"

namespace Util {
    class Ryu : public Fighter  {
    public:
        Ryu();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
    };
}
#endif //RYU_HPP
