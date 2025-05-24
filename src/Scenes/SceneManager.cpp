//
// Created by FanFan on 2025/1/27.
//

#include "Scenes/SceneManager.hpp"

namespace Util {
    void SceneManager::SetContext(std::shared_ptr<Core::Context> context) {
        this->context = context;
    }
    void SceneManager::ChangeSceneType(SceneType newtype) {
        if (NowSceneType != newtype) {
            NowSceneType = newtype;
            auto currentEnter = StateEnter.find(NowSceneType);
            if (currentEnter != StateEnter.end()) {
                currentEnter->second();
            }
        }
    }
    void SceneManager::UpdateState() const {
        auto currentEnter = StateUpdate.find(NowSceneType);
        currentEnter->second();
    }
    void SceneManager::Update() {
        if (m_NowScene!=nullptr) {
            m_NowScene->Update(context);
        }
        UpdateState();
    }
    void SceneManager::StartSceneEnter() {
        ChangeScene(std::make_shared<StartScene>());
        m_NowScene->Init(context);
    }
    void SceneManager::StartSceneUpdate() {
        if(m_NowScene->getSenseEnd()) {
            mode = m_NowScene->getmode();
            std::cout << "Mode selected: " << static_cast<int>(mode) << std::endl;
            Enemies.clear();
            ChangeSceneType(SceneType::Slect);
            //ChangeSceneType(SceneType::Battle);
        }
    }
    void SceneManager::SlectSceneEnter() {
        auto next = std::make_shared<SlectScene>();
        next->SetMode(mode);
        ChangeScene(next);
    }
    void SceneManager::SlectSceneUpdate() {
        if(m_NowScene->getSenseEnd()) {
            auto Now_Scene = std::dynamic_pointer_cast<SlectScene>(m_NowScene);
            player=Now_Scene->GetPlayer1Character();
            if(mode==ModeType::Story) {
                EnemySlect();
                enemy=Enemies[stage_count];
            }
            else{
                enemy=Now_Scene->GetPlayer2Character();
            }
            ChangeSceneType(SceneType::Pass);
        }
    }
    void SceneManager::PassSceneEnter() {
        ChangeScene(std::make_shared<PassScene>(player,enemy));
    }
    void SceneManager::PassSceneUpdate() {
        if(m_NowScene->getSenseEnd()) {
            ChangeSceneType(SceneType::Battle);
        }
    }
    void SceneManager::BattleSceneEnter() {
        ChangeScene(std::make_shared<BattleScene>(player,enemy));

    }
    void SceneManager::BattleSceneUpdate() {
        if (m_NowScene->getSenseEnd()) {
            std::shared_ptr<Scene> nextScene;
            if(mode==ModeType::Battle) {
                ChangeSceneType(SceneType::Slect);
            }
            else if(mode==ModeType::Story){
                auto NowScene=std::dynamic_pointer_cast<BattleScene>(m_NowScene);
                finalresult=NowScene->GetFinalResult();
                ChangeSceneType(SceneType::WinLoss);
            }
        }
    }
    void SceneManager::WinLossSceneEnter() {
        ChangeScene(std::make_shared<WinLossScene>(player,enemy,finalresult));
    }
    void SceneManager::WinLossSceneUpdate() {
        if (m_NowScene->getSenseEnd()) {
            if(finalresult==FinalResult::Player2Win) {
                ChangeSceneType(SceneType::Continue);
            }
            else{
                if (stage_count<7) {
                    stage_count++;//每過一關+1
                    enemy=Enemies[stage_count];
                }
                ChangeSceneType(SceneType::Pass);
            }
            finalresult=FinalResult::Null;
        }
    }
    void SceneManager::ContinueSceneEnter() {
        ChangeScene(std::make_shared<ContinueScene>(player));
    }
    void SceneManager::ContinueSceneUpdate() {
        if (m_NowScene->getSenseEnd()) {
            auto NowScene=std::dynamic_pointer_cast<ContinueScene>(m_NowScene);
            ContinueOrNot=NowScene->GetChooseResult();
            if(ContinueOrNot==ChooseResult::GameOver) {
                stage_count=0;
                ChangeSceneType(SceneType::Start);
            }
            else {
                ChangeSceneType(SceneType::Pass);
            }
            ContinueOrNot=ChooseResult::Null;
        }
    }
    void SceneManager::Render() {
        if (m_NowScene!=nullptr) {
            m_NowScene->Render();
        }
    }
    void SceneManager::EnemySlect() {
        auto Now_Scene = std::dynamic_pointer_cast<SlectScene>(m_NowScene);
        std::cout << "Character selected: " << player->GetName() << std::endl;
        if (Enemies.size() < characters.size() - 1) {
            std::vector<FighterList> sorted_keys;
            // 收集 keys
            for (const auto& [key, _] : characters) {
                sorted_keys.push_back(key);
            }

            // 根據 enum 值排序（小到大）
            std::sort(sorted_keys.begin(), sorted_keys.end());

            // 依序建立敵人
            for (const auto& key : sorted_keys) {
                auto candidate = characters[key](); // 產生角色
                if (typeid(*candidate) != typeid(*player)) {
                    Enemies.push_back(candidate);
                }
            }

            for (const auto& enemy : Enemies) {
                std::cout << "Enemy: " << enemy->GetName() << std::endl;
            }
        }
    }
} // namespace Util
