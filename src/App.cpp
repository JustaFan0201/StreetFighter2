#include "App.hpp"

void App::Start(std::shared_ptr<Core::Context> context) {
    LOG_TRACE("Start");
    //初始化Manager and 推入StartScene
    if (!m_IsInitialized) {
        m_SceneManager.SetContext(context);
        m_SceneManager.ChangeSceneType(Util::SceneType::Start);
        m_IsInitialized = true;
    }
    m_CurrentState = State::UPDATE;
}
void App::Update() {
    //更新and渲染目前場景
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
