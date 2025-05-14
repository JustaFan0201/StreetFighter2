//
// Created by asus on 2025/2/27.
//

#ifndef GUILE_HPP
#define GUILE_HPP

#include "Fighter.hpp"

namespace Util {
    class Guile : public Fighter  {
    public:
        Guile();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
        void LoadSpecialMove()override;
        void SonicBoomStateEnter();
        void SonicBoomStateUpdate();
        void SommersaultStateEnter();
        void SommersaultStateUpdate();
    };

}
#endif //GUILE_HPP
