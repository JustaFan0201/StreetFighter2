//
// Created by asus on 2025/2/27.
//

#ifndef HONDA_HPP
#define HONDA_HPP

#include "Fighter.hpp"

namespace Util {
    class Honda : public Fighter  {
    public:
        Honda();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
        void LoadSpecialMove()override;
        void HeadbuttStateEnter();
        void HeadbuttStateUpdate();
        void HeadbuttRecoveryStateEnter();
        void HeadbuttRecoveryStateUpdate();
        void HundredSlapStateEnter();
        void HundredSlapStateUpdate();
    };
}
#endif //HONDA_HPP
