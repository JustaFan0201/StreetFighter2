//
// Created by FanFan on 2025/1/27.
//

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include <memory>
#include "Scenes/Scene.hpp"
#include "Scenes/StartScene.hpp"
#include "Scenes/SlectScene.hpp"
#include "Scenes/PassScene.hpp"
#include "Scenes/BattleScene.hpp"
namespace Util {
    enum class SceneType {
        Start,
        Slect,
        Pass,
        Battle
    };
    class SceneManager {
    public:
        // 切換場景
        void ChangeScene(std::shared_ptr<Scene> scene);
        // 更新當前場景
        void Update();
        // 渲染當前場景
        void Render();
        int GetMode() const;
        void EnemySlect();
    private:
        SceneType NowSceneType=SceneType::Start;
        std::shared_ptr<Scene> m_NowScene=nullptr;
        int mode=0;
        std::shared_ptr<Fighter> player=std::make_shared<Ryu>();
        std::shared_ptr<Fighter> enemy=std::make_shared<Ken>();

        std::vector<std::shared_ptr<Fighter>> characters = {
            std::make_shared<Ryu>(),    // 指向子類 Ryu
            std::make_shared<Honda>(),  // 指向子類 Honda
            std::make_shared<Blanka>(), // 指向子類 Blanka
            std::make_shared<Guile>(),  // 指向子類 Guile
            std::make_shared<Ken>(),    // 指向子類 Ken
            std::make_shared<Chunli>(), // 指向子類 Chunli
            std::make_shared<Zangief>(),// 指向子類 Zangief
            std::make_shared<Dhalsim>() // 指向子類 Dhalsim
        };
        std::vector<std::shared_ptr<Fighter>> Enemies = {};
        int stage_count=0;
    };

} // namespace Util

#endif // SCENEMANAGER_HPP
