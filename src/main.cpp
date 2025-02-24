#include <iostream>
#include <ostream>

#include "App.hpp"
#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    context->SetWindowIcon("../sencepicture/start/icon.png");

    App app;
    // 啟動遊戲
    app.Start();

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();  // 如果有需要可以重新進入啟動狀態
                break;

            case App::State::UPDATE:
                app.Update();  // 更新遊戲邏輯
                break;

            case App::State::END:
                app.End();  // 結束遊戲
                context->SetExit(true);
                break;
        }

        context->Update();  // 更新應用程式上下文（視窗管理等）
    }

    return 0;
}