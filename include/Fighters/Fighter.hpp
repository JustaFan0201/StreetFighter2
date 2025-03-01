//
// Created by asus on 2025/2/27.
//

#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include <memory>
#include <iostream>
#include "Core/Context.hpp"
#include "Util/BGM.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/Transform.hpp"
#include "Util/Time.hpp"
#include "Util/SFX.hpp"

#include "AnimationSpace.hpp"
#include "ImageSpace.hpp"
#include "Word.hpp"

namespace Util {
    class Fighter  {
    public:
        Fighter(const std::string& name)
                    : m_name(name) {}
        virtual ~Fighter() = default;
        // 初始化場景

        std::shared_ptr<ImageSpace> GetFace() const { return face; }
        std::shared_ptr<ImageSpace> GetNameTag() const { return nametag; }
        std::shared_ptr<ImageSpace> GetCountry() const { return country; }
        Transform GetCountryPosition() const { return country_position; }
        std::string GetName() const { return m_name; }
    protected:
        std::shared_ptr<ImageSpace> face;
        std::shared_ptr<ImageSpace> nametag;
        std::shared_ptr<ImageSpace> country;
        Transform country_position;

        std::shared_ptr<AnimationSpace> m_image;
        std::shared_ptr<BGM> m_BGM;
        std::string m_name;
        Transform m_transform;
        int velocity = 0;
    };
}
#endif //FIGHTER_HPP
