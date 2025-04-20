//
// Created by Gs0n on 25-3-7.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Fighters/Fighter.hpp"
#include "Util/Transform.hpp"
#include "Util/Input.hpp"
namespace Util {
    class Camera {
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        float maxOffsetX;
        glm::vec2 cameraPos;
        float boundary=200;
    public:
        void Init(std::shared_ptr<Fighter> player,std::shared_ptr<Fighter> enemy);
        void Upload(float MaxWidth);
        void SetMaxOffsetX(float border);
        int GetMaxOffsetX();
        glm::vec2 GetCameraPos();
    };
}

#endif //CAMERA_HPP