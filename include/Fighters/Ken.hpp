//
// Created by asus on 2025/2/27.
//

#ifndef KEN_HPP
#define KEN_HPP

#include "Fighter.hpp"

namespace Util {
    class Ken : public Fighter  {
    public:
        Ken();
        void LoadAnimations() override;
        /*void IdleStateEnter()override;
        void IdleStateUpload()override;
        void ForwardStateEnter()override;
        void ForwardStateUpload()override;
        void BackwardStateEnter()override;
        void BackwardStateUpload()override;
        void LPStateEnter()override;
        void LPStateUpload()override;
        void MPStateEnter()override;
        void MPStateUpload()override;*/
    };
}
#endif //KEN_HPP
