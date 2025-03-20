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

            auto animation = std::dynamic_pointer_cast<Animation>(m_Drawable);
            int currentInterval = GetIntervalForFrame(animation->GetCurrentFrameIndex());
            animation->SetInterval(currentInterval);

            glm::vec2 currentOffset = Getoffset(animation->GetCurrentFrameIndex());
            Transform transform={m_Transform.translation+currentOffset,0,m_Transform.scale};

            auto data = ConvertToUniformBufferData(
                transform, custom_size, m_ZIndex);
            data.m_Model = translate(
                data.m_Model, glm::vec3{m_Pivot / custom_size, 0} * -1.0F);

            m_Drawable->Draw(data);
        }
        void SetDrawData(Transform transform, glm::vec2 size, float index) {
            SetSize(size);
            SetTransform(transform);
            SetZIndex(index);
        }

        void SetTransformXY(glm::vec2 postion) {
            m_Transform.translation=postion;
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

        void Setoffset(const std::vector<glm::vec2>& offsets) {
            frameOffset = offsets;
        }

        glm::vec2 Getoffset(std::size_t frameIndex) {
            auto animation = std::dynamic_pointer_cast<Animation>(m_Drawable);
            if (frameIndex < frameOffset.size()) {
                return frameOffset[frameIndex];
            }
            return {0,0};
        }
        void SetOriginalPostion(const glm::vec2 Original) {
            originalPostion=Original;
        }
        glm::vec2 GetOriginalPostion() const {
            return originalPostion;
        }
    private:
        glm::vec2 custom_size;
        std::vector<int> frameIntervals;
        std::vector<glm::vec2> frameOffset;
        glm::vec2 originalPostion;
    };
} // namespace Util
#endif //ANIMATIONSPACE_HPP
