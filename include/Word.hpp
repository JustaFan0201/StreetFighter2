//
// Created by asus on 2025/2/25.
//

#ifndef WORD_HPP
#define WORD_HPP
#include "Util/GameObject.hpp"
#include "Util/Color.hpp"
#include "Util/Text.hpp"
#include "Util/TransformUtils.hpp"

namespace Util {
    class Word : public GameObject {
    public:
        Word(const std::string &fontPath, int fontSize, const std::string &text,
             const Color &color, float zIndex = 0.0f)
            : GameObject(std::make_shared<Text>(fontPath, fontSize, text, color), zIndex) {}

        void SetText(const std::string &text) {
            std::dynamic_pointer_cast<Text>(m_Drawable)->SetText(text);
        }

        void SetColor(const Color &color) {
            std::dynamic_pointer_cast<Text>(m_Drawable)->SetColor(color);
        }

        void custom_Draw() {
            if (!m_Visible || m_Drawable == nullptr) {
                return;
            }

            auto data = Util::ConvertToUniformBufferData(
                m_Transform, custom_size, m_ZIndex);
            data.m_Model = glm::translate(
                data.m_Model, glm::vec3{m_Pivot / custom_size, 0} * -1.0F);

            m_Drawable->Draw(data);
        }
        void SetDraw(Transform transform,glm::vec2 size,float index) {
            custom_size=size;
            m_Transform=transform;
            SetZIndex(index);
        }
        std::shared_ptr<Core::Drawable> GetDrawable() {
            return m_Drawable;
        }
    private:
        glm::vec2 custom_size;
    };
} // namespace Util
#endif //WORD_HPP
