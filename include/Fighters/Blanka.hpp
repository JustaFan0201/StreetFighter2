//
// Created by asus on 2025/2/27.
//

#ifndef BLANKA_HPP
#define BLANKA_HPP
#include <memory>
#include <string>

#include "Fighter.hpp"

namespace Util {
    class Blanka : public Fighter  {
    public:
        Blanka();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
        void LoadSpecialMove()override;
        void ElectricThunderStateEnter();
        void ElectricThunderStateUpdate();
        void RollingAttackStateEnter();
        void RollingAttackStateUpdate();
        void RollingAttackRecoveryStateEnter();
        void RollingAttackRecoveryStateUpdate();
    };
}
#endif //BLANKA_HPP
