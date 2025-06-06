//
// Created by asus on 2025/2/27.
//

#ifndef ZANGIEF_HPP
#define ZANGIEF_HPP

#include "Fighter.hpp"

namespace Util {
    class Zangief : public Fighter  {
    public:
        Zangief();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
        void LoadSpecialMove()override;
        void DoubleLariatStateEnter();
        void DoubleLariatStateUpdate();
    };
}
#endif //ZANGIEF_HPP
