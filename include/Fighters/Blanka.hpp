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
        void LoadSpecialMove();
        void ElectricThunderStateEnter();
        void ElectricThunderStateUpload();
        void RollingAttackStateEnter();
        void RollingAttackStateUpload();
        void RollingAttackRecoveryStateEnter();
        void RollingAttackRecoveryStateUpload();
    };
}
#endif //BLANKA_HPP
