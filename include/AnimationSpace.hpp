//
// Created by asus on 2025/2/25.
//

#ifndef ANIMATIONSPACE_HPP
#define ANIMATIONSPACE_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Util/TransformUtils.hpp"

namespace Util {
    class AnimationSpace : public GameObject {
    public:
        AnimationSpace(const std::vector<std::string> &frames, bool loop = true,
                       int duration = 2000, bool autoStart = false,
                       float zIndex = 0.0f)
            : GameObject(std::make_shared<Animation>(frames, loop, duration, autoStart, 0), zIndex) {}

        void custom_Draw() {//自訂義畫出
            if (!m_Visible || m_Drawable == nullptr) {
                return;
            }

            auto data = Util::ConvertToUniformBufferData(
                m_Transform, custom_size, m_ZIndex);
            data.m_Model = glm::translate(
                data.m_Model, glm::vec3{m_Pivot / custom_size, 0} * -1.0F);

            m_Drawable->Draw(data);
        }

        void SetDrawData(Transform transform,glm::vec2 size,float index) {//設定x,y,size,z
            SetSize(size);
            SetTransform(transform);
            SetZIndex(index);
        }
        void SetMatchFloor(float groundLevel) {//讓角色底部對齊地板
            m_Transform.translation.y = groundLevel + custom_size.y / 2;
        }
        void SetTransform(Transform transform) {
            m_Transform=transform;
        }
        void SetSize(glm::vec2 size){
            custom_size=size;
        }
        std::shared_ptr<Core::Drawable> GetDrawable() {
            return m_Drawable;
        }
        glm::vec2 GetCustomSize() {
            return custom_size;
        }
        glm::vec2 GetOriginalSize() {
            return m_Drawable->GetSize();
        }
    private:
        glm::vec2 custom_size;
    };
} // namespace Util
#endif //ANIMATIONSPACE_HPP
