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

        void SetText(const std::string &text) {//設定文字
            std::dynamic_pointer_cast<Text>(m_Drawable)->SetText(text);
        }

        void SetColor(const Color &color) {//設定顏色
            std::dynamic_pointer_cast<Text>(m_Drawable)->SetColor(color);
        }

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
        void SetTransform(Transform transform) {
            m_Transform=transform;
        }
        void SetSize(glm::vec2 size){
            custom_size=size;
        }
        std::shared_ptr<Core::Drawable> GetDrawable() {
            return m_Drawable;
        }
    private:
        glm::vec2 custom_size;
    };
} // namespace Util
#endif //WORD_HPP
