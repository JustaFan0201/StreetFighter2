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
        void LoadSpecialMove();
        void HeadbuttStateEnter();
        void HeadbuttStateUpload();
        void HeadbuttRecoveryStateEnter();
        void HeadbuttRecoveryStateUpload();
        void HundredSlapStateEnter();
        void HundredSlapStateUpload();
    };
}
#endif //HONDA_HPP
