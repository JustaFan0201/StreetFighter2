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


namespace Util {
    class Scene {
    public:
        virtual ~Scene() = default;
        // 初始化場景
        virtual void Init() = 0;
        // 更新場景
        virtual void Update() = 0;
        // 渲染場景
        virtual void Render() = 0;
        bool getSenseEnd() const;//判斷場景是否能結束
    protected:
        std::shared_ptr<AnimationSpace> m_Animation;
        std::shared_ptr<BGM> m_BGM;
        bool SenseEnd=false;
        float start_time = Time::GetElapsedTimeMs();
    };
} // namespace Util

#endif // SCENE_HPP
