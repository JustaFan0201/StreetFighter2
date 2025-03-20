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

        void IdleStateEnter()override;
        void IdleStateUpload()override;

        void WalkStateEnter()override;
        void WalkStateUpload()override;
        void JumpStateEnter()override;
        void JumpStateUpload()override;

        void LPStateEnter()override;
        void LPStateUpload()override;
        void MPStateEnter()override;
        void MPStateUpload()override;
        void LKStateEnter()override;
        void LKStateUpload()override;
        void MKStateEnter()override;
        void MKStateUpload()override;
        void HKStateEnter()override;
        void HKStateUpload()override;


    };
}
#endif //RYU_HPP
