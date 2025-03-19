#ifndef ANIMATIONSPACE_HPP
#define ANIMATIONSPACE_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Util/TransformUtils.hpp"
#include <unordered_map>
#include <vector>

namespace Util {
    class AnimationSpace : public GameObject {
    public:
        AnimationSpace(const std::vector<std::string> &frames, bool loop = true,
                       int duration = 2000, bool autoStart = false,
                       float zIndex = 0.0f)
            : GameObject(std::make_shared<Animation>(frames, loop, duration, autoStart, 0), zIndex) {}

        void custom_Draw(){
            if (!m_Visible || m_Drawable == nullptr) {
                return;
            }

            // 获取当前帧的间隔
            auto animation = std::dynamic_pointer_cast<Animation>(m_Drawable);
            int currentInterval = GetIntervalForFrame(animation->GetCurrentFrameIndex());

            // 更新动画间隔
            animation->SetInterval(currentInterval);

            auto data = Util::ConvertToUniformBufferData(
                m_Transform, custom_size, m_ZIndex);
            data.m_Model = glm::translate(
                data.m_Model, glm::vec3{m_Pivot / custom_size, 0} * -1.0F);

            m_Drawable->Draw(data);
        }
        void SetDrawData(Transform transform, glm::vec2 size, float index) {
            SetSize(size);
            SetTransform(transform);
            SetZIndex(index);
        }

        void SetLeftDownBeCenter() {
            m_Transform.translation.y += custom_size.y / 2;
            m_Transform.translation.x += custom_size.x / 2;
        }

        void SetRightDownBeCenter() {
            m_Transform.translation.y += custom_size.y / 2;
            m_Transform.translation.x -= custom_size.x / 2;
        }

        void SetTransform(Transform transform) {
            m_Transform = transform;
        }

        void SetSize(glm::vec2 size) {
            custom_size = size;
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

        glm::vec2 GetPivot() {
            return m_Pivot;
        }

        bool IsAnimationEnds() const {
            auto animation = std::dynamic_pointer_cast<Animation>(m_Drawable);
            return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
        }

        void SetCooldown(float cooldown) const {
            auto animation = std::dynamic_pointer_cast<Animation>(m_Drawable);
            animation->SetCooldown(cooldown);
        }

        void SetFrameIntervals(const std::vector<int>& intervals) {
            frameIntervals = intervals;
        }

        int GetIntervalForFrame(std::size_t frameIndex) {
            auto animation = std::dynamic_pointer_cast<Animation>(m_Drawable);
            if (frameIndex < frameIntervals.size()) {
                return frameIntervals[frameIndex];
            }
            return animation->GetInterval();
        }

    private:
        glm::vec2 custom_size;
        std::vector<int> frameIntervals;  // 儲存每幀的間隔
    };
} // namespace Util
#endif //ANIMATIONSPACE_HPP
