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
        void DoubleKneePressStateEnter();
        void DoubleKneePressStateUpdate();
        void PsychoCrusherStateEnter();
        void PsychoCrusherStateUpdate();
        void HeadStompStateEnter();
        void HeadStompStateUpdate();
        void HeadStompAttackStateEnter();
        void HeadStompAttackStateUpdate();
        void HeadStompRecoveryStateEnter();
        void HeadStompRecoveryStateUpdate();
        void HeadStompDeriveStateEnter();
        void HeadStompDeriveStateUpdate();
    };
}
#endif //VEGA_HPP
