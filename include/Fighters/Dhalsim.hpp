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
    };
}
#endif //DHALSIM_HPP
