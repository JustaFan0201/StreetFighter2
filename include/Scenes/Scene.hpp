//
// Created by FanFan on 2025/1/27.
//

#ifndef SCENE_HPP
#define SCENE_HPP
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

#include "Fighters/Fighter.hpp"
#include "Fighters/Ryu.hpp"
#include "Fighters/Guile.hpp"
#include "Fighters/Zangief.hpp"
#include "Fighters/Chunli.hpp"
#include "Fighters/Dhalsim.hpp"
#include "Fighters/Blanka.hpp"
#include "Fighters/Ken.hpp"
#include "Fighters/Honda.hpp"
enum class ModeType {
    Story,
    Battle
};
namespace Util {
    class Scene {
    public:
        virtual ~Scene() = default;
        virtual void Init(std::shared_ptr<Core::Context> context) = 0;//初始化
        virtual void Update(std::shared_ptr<Core::Context> context) = 0;//更新
        virtual void Render() = 0;//渲染
        bool getSenseEnd() const;//判斷場景能否結束 true=結束 false=繼續
        void SetMode(ModeType modetype){mode=modetype;}
    protected:
        ModeType mode=ModeType::Story;
        std::shared_ptr<AnimationSpace> m_Animation;//背景
        std::shared_ptr<BGM> m_BGM;
        bool SenseEnd=false;
        float start_time = Time::GetElapsedTimeMs();//進場景開始計時
    };
}
#endif // SCENE_HPP
