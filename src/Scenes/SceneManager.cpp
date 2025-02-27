//
// Created by FanFan on 2025/1/27.
//

#include "Scenes/SceneManager.hpp"

#include <iostream>
#include <ostream>

namespace Util {

    void SceneManager::PushScene(std::shared_ptr<Scene> scene) {
        m_SceneStack.push(scene);
        scene->Init();
    }

    void SceneManager::ChangeScene(std::shared_ptr<Scene> scene) {
        if (!m_SceneStack.empty()) {
            m_SceneStack.pop();
        }
        PushScene(scene);
    }

    void SceneManager::Update() {
        if (!m_SceneStack.empty()) {
            m_SceneStack.top()->Update();
        }

        if (!m_SceneStack.empty() && m_SceneStack.top()->getSenseEnd() && typeid(*m_SceneStack.top()) == typeid(StartScene)) {
            mode = m_SceneStack.top()->getmode(); // 取得 mode
            std::cout << "Mode selected: " << mode << std::endl;

            // 根據 mode 切換到對應的場景
            std::shared_ptr<Scene> nextScene;
            if (mode == 0) {
                nextScene = std::make_shared<SlectScene>();  // 切換到 Story 模式
            } else {
                nextScene = std::make_shared<SlectScene>(); // 切換到 Battle 模式
            }
            ChangeScene(nextScene);
        }
    }

    void SceneManager::Render() {
        if (!m_SceneStack.empty()) {
            m_SceneStack.top()->Render();
        }
    }
    int  SceneManager::GetMode() const {
        return mode;
    }

} // namespace Util
