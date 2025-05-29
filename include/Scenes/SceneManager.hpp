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
#include "WinLossScene.hpp"
#include "ContinueScene.hpp"
namespace Util {
    enum class SceneType {
        Null,
        Start,
        Slect,
        Pass,
        Battle,
        WinLoss,
        Continue
    };
    class SceneManager {
    public:
        SceneManager() {
            StateEnter[SceneType::Start] = [this] { StartSceneEnter(); };
            StateEnter[SceneType::Slect] = [this] { SlectSceneEnter(); };
            StateEnter[SceneType::Pass] = [this] { PassSceneEnter(); };
            StateEnter[SceneType::Battle] = [this] { BattleSceneEnter(); };
            StateEnter[SceneType::WinLoss] = [this] { WinLossSceneEnter(); };
            StateEnter[SceneType::Continue] = [this] { ContinueSceneEnter(); };

            StateUpdate[SceneType::Start] = [this] {StartSceneUpdate(); };
            StateUpdate[SceneType::Slect] = [this] {SlectSceneUpdate(); };
            StateUpdate[SceneType::Pass] = [this] {PassSceneUpdate(); };
            StateUpdate[SceneType::Battle] = [this] {BattleSceneUpdate(); };
            StateUpdate[SceneType::WinLoss] = [this] {WinLossSceneUpdate(); };
            StateUpdate[SceneType::Continue] = [this] {ContinueSceneUpdate();};
        }
        void ChangeSceneType(SceneType newtype);//切場景
        void ChangeScene(const std::shared_ptr<Scene> &NewScene){m_NowScene=NewScene;m_NowScene->Init(context);}//切場景
        void Update();
        void Render();
        void EnemySlect();//生成敵人vector Enemies
        void DetectedPassedGame();
        void SetContext(std::shared_ptr<Core::Context> context);
        [[nodiscard]] ModeType GetMode() const{return mode;}//取模式
        void UpdateState() const;
        void StartSceneEnter();
        void StartSceneUpdate();
        void SlectSceneEnter();
        void SlectSceneUpdate();
        void PassSceneEnter();
        void PassSceneUpdate();
        void BattleSceneEnter();
        void BattleSceneUpdate();
        void WinLossSceneEnter();
        void WinLossSceneUpdate();
        void ContinueSceneEnter();
        void ContinueSceneUpdate();
    private:
        std::shared_ptr<Core::Context> context;

        SceneType NowSceneType=SceneType::Null;
        std::unordered_map<SceneType, std::function<void()>> StateEnter;
        std::unordered_map<SceneType, std::function<void()>> StateUpdate;
        std::shared_ptr<Scene> m_NowScene=nullptr;//目前場景

        ModeType mode=ModeType::Story;//0=story 1=battle
        ChooseResult ContinueOrNot=ChooseResult::Null;//0=story 1=battle
        std::shared_ptr<Fighter> player=std::make_shared<Zangief>();
        std::shared_ptr<Fighter> enemy=std::make_shared<Vega>();

        std::pmr::unordered_map<FighterList, std::function<std::shared_ptr<Fighter>()>> characters = {
            {FighterList::Ryu,     []() { return std::make_shared<Ryu>(); }},
            {FighterList::Honda,   []() { return std::make_shared<Honda>(); }},
            {FighterList::Blanka,  []() { return std::make_shared<Blanka>(); }},
            {FighterList::Guile,   []() { return std::make_shared<Guile>(); }},
            {FighterList::Ken,     []() { return std::make_shared<Ken>(); }},
            {FighterList::Chunli,  []() { return std::make_shared<Chunli>(); }},
            {FighterList::Zangief, []() { return std::make_shared<Zangief>(); }},
            {FighterList::Dhalsim, []() { return std::make_shared<Dhalsim>(); }},
            {FighterList::Vega, []() { return std::make_shared<Vega>(); }}
        };
        std::vector<std::shared_ptr<Fighter>> Enemies = {};//敵人vector
        int stage_count=0;//目前關卡
        bool PassedGame=false;
        FinalResult finalresult=FinalResult::Null;
    };
}

#endif // SCENEMANAGER_HPP
