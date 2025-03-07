//
// Created by Gs0n on 25-3-7.
//

#include "Scenes/Camera.hpp"

namespace Util {
    void Camera::Init() {
        maxOffsetX = 0;
        cameraPos = {0,0};
    }
    void Camera::Upload() {
        int moveSpeed = 10;
        if (Input::IsKeyPressed(Keycode::A)) {
            cameraPos.x -= moveSpeed;
        }
        else if (Input::IsKeyPressed(Keycode::D)) {
            cameraPos.x += moveSpeed;
        }
        if (cameraPos.x < -maxOffsetX ) cameraPos.x = -maxOffsetX ;
        if (cameraPos.x >  maxOffsetX ) cameraPos.x = maxOffsetX ;
    }
    void Camera::SetMaxOffsetX( int border) {
        maxOffsetX = border;
    }
    int Camera::GetMaxOffsetX() {
        return maxOffsetX;
    }
    glm::vec2 Camera::GetCameraPos() {
        return  cameraPos;
    }


}
