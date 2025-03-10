#ifndef APP_HPP
#define APP_HPP
#include "Scenes/SceneManager.hpp"
#include "Scenes/Scene.hpp"
#include "pch.hpp" // IWYU pragma: export

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

    void Start(std::shared_ptr<Core::Context> context);

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();
    State m_CurrentState = State::START;
    Util::SceneManager m_SceneManager; // 場景管理器
    bool m_IsInitialized = false; // 是否已經初始化
};

#endif
