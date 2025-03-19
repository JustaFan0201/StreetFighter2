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
    };
}
#endif //KEN_HPP
