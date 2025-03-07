//
// Created by FanFan on 2025/1/27.
//

#include "Scenes/SceneManager.hpp"

namespace Util {
    void SceneManager::ChangeScene(std::shared_ptr<Scene> scene) {
        m_NowScene=scene;
        m_NowScene->Init();
    }

    void SceneManager::Update() {
        if (m_NowScene!=nullptr) {
            m_NowScene->Update();
        }

        if (m_NowScene!=nullptr && m_NowScene->getSenseEnd() && NowSceneType==SceneType::Start) {
            if (auto Now_Scene = std::dynamic_pointer_cast<StartScene>(m_NowScene)) {
                mode = Now_Scene->getmode(); //取mode
            }
            std::cout << "Mode selected: " << mode << std::endl;
            std::shared_ptr<Scene> nextScene;
            if (mode == 0) {
                nextScene = std::make_shared<SlectScene>(); //切到Story模式
            } else {
                nextScene = std::make_shared<SlectScene>(); //切到Battle模式
            }
            NowSceneType=SceneType::Slect;
            ChangeScene(nextScene);
        }
        if (m_NowScene!=nullptr && m_NowScene->getSenseEnd() && NowSceneType==SceneType::Slect) {
            EnemySlect();
            std::shared_ptr<Scene> nextScene;
            if (stage_count<7) {
                enemy=Enemies[stage_count++];//每過一關+1
            }
            nextScene = std::make_shared<PassScene>(player,enemy); //pass scene
            NowSceneType=SceneType::Pass;
            ChangeScene(nextScene);
        }
        if (m_NowScene!=nullptr && m_NowScene->getSenseEnd() && NowSceneType==SceneType::Pass) {
            std::shared_ptr<Scene> nextScene;
            nextScene = std::make_shared<BattleScene>(player,enemy); //battle scene
            NowSceneType=SceneType::Battle;
            ChangeScene(nextScene);
        }
        if (m_NowScene!=nullptr && m_NowScene->getSenseEnd() && NowSceneType==SceneType::Battle) {
            std::shared_ptr<Scene> nextScene;
            nextScene = std::make_shared<SlectScene>();
            NowSceneType=SceneType::Slect;
            ChangeScene(nextScene);
        }
    }

    void SceneManager::Render() {
        if (m_NowScene!=nullptr) {
            m_NowScene->Render();
        }
    }
    int  SceneManager::GetMode() const {
        return mode;
    }
    void SceneManager::EnemySlect() {
        if (auto Now_Scene = std::dynamic_pointer_cast<SlectScene>(m_NowScene)) {
            if (player!=Now_Scene->GetPlayerCharacter()) {
                player = Now_Scene->GetPlayerCharacter(); //取得遊玩角色
            }
            std::cout << "Character selected: " << player->GetName() << std::endl;
        }
        if (Enemies.size()<characters.size()-1) {//生成Enemies
            for (auto character : characters) {
                if (typeid(*player) != typeid(*character)) {
                    Enemies.push_back(character);
                }
            }
            for (auto character : Enemies) {
                std::cout << "Enemy: " << character->GetName() << std::endl;
            }
        }
    }
} // namespace Util
