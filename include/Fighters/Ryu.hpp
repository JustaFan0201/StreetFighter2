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
        void LoadSpecialMove()override;
        void HandoukenStateEnter();
        void HandoukenStateUpdate();
        void ShoryukenStateEnter();
        void ShoryukenStateUpdate();
        void TatsumakiSenpuStateEnter();
        void TatsumakiSenpuStateUpdate();
    };
}
#endif //RYU_HPP
