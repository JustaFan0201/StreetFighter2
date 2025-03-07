//
// Created by asus on 2025/2/27.
//

#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include <memory>
#include <iostream>
#include <string>
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
        Fighter(const std::string& name): m_name(name) {}
        virtual ~Fighter() = default;

        std::shared_ptr<ImageSpace> GetFace() const { return face; }
        std::shared_ptr<ImageSpace> GetNameTag() const { return nametag; }
        std::shared_ptr<ImageSpace> GetCountry() const { return country; }
        Transform GetCountryPosition() const { return country_position; }
        std::vector<std::string> GetStageBackground() { return stage_background; }
        std::string GetName() const { return m_name; }
        std::shared_ptr<BGM> GetBGM() { return m_BGM; }

        void BackgroundInit(int picture_number);
        std::vector<std::string> ActionInit(int picture_number,std::string Action);
        //輸入frame (num)圖數量 圖放在對應角色資料夾 Action輸入資料夾名稱

        void Upload();
        void DrawCharacter();
    protected:
        std::shared_ptr<ImageSpace> face;
        std::shared_ptr<ImageSpace> nametag;
        std::shared_ptr<ImageSpace> country;
        Transform country_position;
        std::vector<std::string> stage_background;

        std::vector<std::string> Idle;

        std::shared_ptr<AnimationSpace> ActionNow;
        std::shared_ptr<BGM> m_BGM;
        std::string m_name;
        int velocity = 0;
    };
}
#endif //FIGHTER_HPP
