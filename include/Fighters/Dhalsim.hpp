//
// Created by asus on 2025/2/27.
//

#ifndef DHALSIM_HPP
#define DHALSIM_HPP

#include "Fighter.hpp"

namespace Util {
    class Dhalsim : public Fighter  {
    public:
        Dhalsim();
        void LoadAnimations() override;
        void LoadOffsetVelocity() override;
        void LoadAllBox()override;
        void LoadSpecialMove()override;
        void YogaFireStateEnter();
        void YogaFireStateUpdate();
        void YogaFlameStateEnter();
        void YogaFlameStateUpdate();

        void CrouchAttackStateEnter();
        void CrouchAttackStateUpdate();
    };
}
#endif //DHALSIM_HPP
