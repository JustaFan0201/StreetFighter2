//
// Created by Gs0n on 25-3-10.
//

#ifndef BLOODSTICK_HPP
#define BLOODSTICK_HPP

#include <memory>
#include <string>
#include "ImageSpace.hpp"
#include "Util/Time.hpp"

namespace Util {
    class Bloodstick {
    private:
        std::string original;
        std::shared_ptr<ImageSpace> bloodstick_image;

    public:
        Bloodstick();
        void DrawBloodstick();
    };
}

#endif //BLOODSTICK_HPP


