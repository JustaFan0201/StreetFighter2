#ifndef APP_HPP
#define APP_HPP
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "pch.hpp" // IWYU pragma: export

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    Util::SceneManager m_SceneManager; // 場景管理器
    bool m_IsInitialized = false; // 是否已經初始化
};

#endif
