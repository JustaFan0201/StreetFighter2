//
// Created by Gs0n on 25-3-7.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Util/Transform.hpp"
#include "Util/Input.hpp"
namespace Util {
    class Camera {
    private:
        int maxOffsetX;
        glm::vec2 cameraPos;
    public:
        void Upload();
        void Init();
        void SetMaxOffsetX(int border);
        int GetMaxOffsetX();
        glm::vec2 GetCameraPos();
    };
}

#endif //CAMERA_HPP