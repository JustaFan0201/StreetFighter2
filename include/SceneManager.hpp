//
// Created by FanFan on 2025/1/27.
//

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "../include/Scene.hpp"
#include <memory>
#include <stack>
#include "StartScene.hpp"
#include "SlectScene.hpp"
namespace Util {

    class SceneManager {
    public:
        // 推入一個新的場景
        void PushScene(std::shared_ptr<Scene> scene);

        // 切換場景
        void ChangeScene(std::shared_ptr<Scene> scene);

        // 更新當前場景
        void Update();

        // 渲染當前場景
        void Render();
        int GetMode() const;
    private:
        std::stack<std::shared_ptr<Scene>> m_SceneStack;
        int mode=0;
    };

} // namespace Util

#endif // SCENEMANAGER_HPP
