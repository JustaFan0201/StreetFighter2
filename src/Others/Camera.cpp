//
// Created by Gs0n on 25-3-7.
//

#include "Others/Camera.hpp"

namespace Util {
    void Camera::Init(std::shared_ptr<Fighter> player,std::shared_ptr<Fighter> enemy) {
        this->player=player;
        this->enemy=enemy;
        maxOffsetX = 0;
        cameraPos = {0,0};
    }
    void Camera::Upload() {
        float playerX = player->GetCurrentPosition().x;
        float enemyX = enemy->GetCurrentPosition().x;

        float lowerX = std::min(playerX, enemyX);
        float higherX = std::max(playerX, enemyX);
        float distance = higherX - lowerX;
        float center = (playerX + enemyX) / 2.0f;

        // 若距離太遠，保持角色邊緣在畫面內
        if (distance > (2 * maxOffsetX - boundary * 2)) {
            cameraPos.x= lowerX + distance / 2.0f;
        } else {
            cameraPos.x = center;
        }
        /*
        for (auto& fighter : std::vector{player, enemy}) {
            float fighterX = fighter->GetCurrentPosition().x;
            float fighterVelocityX = fighter->GetVelocity().x;
            int fighterDirection = fighter->GetDirection();
            std::cout << cameraPos.x <<"||"<<fighterVelocityX<<"||"<< std::endl;
            // 角色在畫面左側推左
            if (fighterX < cameraPos.x - maxOffsetX + boundary && fighterVelocityX * fighterDirection < 0) {
                cameraPos.x += fighterVelocityX * fighterDirection*Time::GetDeltaTimeMs()/1000;
            }

            // 角色在畫面右側推右
            if (fighterX > cameraPos.x + maxOffsetX - boundary && fighterVelocityX * fighterDirection > 0) {
                cameraPos.x += fighterVelocityX * fighterDirection*Time::GetDeltaTimeMs()/1000;
            }
        }*/

        if (cameraPos.x < -maxOffsetX) cameraPos.x = -maxOffsetX;
        if (cameraPos.x >  maxOffsetX) cameraPos.x =  maxOffsetX;
    }
    void Camera::SetMaxOffsetX(float border) {
        maxOffsetX = border;
    }
    int Camera::GetMaxOffsetX() {
        return maxOffsetX;
    }
    glm::vec2 Camera::GetCameraPos() {
        return  cameraPos;
    }
}
