//
// Created by asus on 2025/2/27.
//

#ifndef CHUNLI_HPP
#define CHUNLI_HPP

#include "Fighter.hpp"

namespace Util {
    class Chunli : public Fighter  {
    public:
        Chunli();
        void LoadAnimations() override;
    };
}
#endif //CHUNLI_HPP
