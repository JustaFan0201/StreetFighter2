#include "App.hpp"

void App::Start() {
    LOG_TRACE("Start");

    // 初始化場景管理器並推入 StartScene
    if (!m_IsInitialized) {
        std::shared_ptr<Util::StartScene> startScene = std::make_shared<Util::StartScene>();
        m_SceneManager.ChangeScene(startScene);
        m_IsInitialized = true;
    }

    m_CurrentState = State::UPDATE; // 當前狀態切換為 UPDATE
}

void App::Update() {
    // 更新當前場景
    m_SceneManager.Update();
    m_SceneManager.Render();


    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
