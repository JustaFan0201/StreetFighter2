//
// Created by FanFan on 2025/1/27.
//

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Scene.hpp"
#include "StartScene.hpp"
#include "SlectScene.hpp"
#include "PassScene.hpp"
#include "BattleScene.hpp"
namespace Util {
    enum class SceneType {
        Start,
        Slect,
        Pass,
        Battle
    };
    class SceneManager {
    public:
        void ChangeScene(std::shared_ptr<Scene> scene);//切場景
        void Update();
        void Render();
        void EnemySlect();//生成敵人vector Enemies
        void SetContext(std::shared_ptr<Core::Context> context);
        [[nodiscard]] ModeType GetMode() const{return mode;}//取模式
    private:
        std::shared_ptr<Core::Context> context;
        SceneType NowSceneType=SceneType::Start;//目前階段
        std::shared_ptr<Scene> m_NowScene=nullptr;//目前場景
        ModeType mode=ModeType::Story;//0=story 1=battle
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
        std::vector<std::shared_ptr<Fighter>> Enemies = {};//敵人vector
        int stage_count=0;//目前關卡
    };
}

#endif // SCENEMANAGER_HPP
