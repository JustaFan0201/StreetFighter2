//
// Created by Gs0n on 25-3-10.
//

#ifndef BLOODSTICK_HPP
#define BLOODSTICK_HPP

#include <memory>
#include <string>
#include "ImageSpace.hpp"
#include"AnimationSpace.hpp"
#include "Util/Transform.hpp"
#include "Util/Time.hpp"

#include "Fighters/Fighter.hpp"
#include "Fighters/Ryu.hpp"
#include "Fighters/Guile.hpp"
#include "Fighters/Zangief.hpp"
#include "Fighters/Chunli.hpp"
#include "Fighters/Dhalsim.hpp"
#include "Fighters/Blanka.hpp"
#include "Fighters/Ken.hpp"
#include "Fighters/Honda.hpp"

namespace Util {
    enum class State{
        Null,
        Round,
        Fight,
        FightEnd,
        WaitForEnd,
        TimeOver,
        EndEventLoss,
        EndEventWin,
        End
    };
    class UI {
    private:
        std::shared_ptr<ImageSpace> bloodback_image;
        std::shared_ptr<ImageSpace> ko_image;
        std::shared_ptr<ImageSpace> bloodfrontP1_image;
        std::shared_ptr<ImageSpace> bloodfrontP2_image;
        std::shared_ptr<ImageSpace> timerTens_image;
        std::shared_ptr<ImageSpace> timerUnits_image;
        std::shared_ptr<ImageSpace> fight_image;
        std::shared_ptr<ImageSpace> round_image;
        std::shared_ptr<ImageSpace> roundnum_image;
        std::vector<std::shared_ptr<ImageSpace>> PlayerWinCountImage,EnemyWinCountImage;
        int PlayerWinCounter=0,EnemyWinCounter=0;

        std::shared_ptr<SFX> soundeffect;
        State currentState=State::Null;
        bool RoundStartIsEnd=false;
        float start_time = Time::GetElapsedTimeMs();

        std::shared_ptr<Fighter> P1;
        std::shared_ptr<Fighter> P2;

        std::vector<std::string> namebox = {"Ryu", "Honda", "Blanka", "Guile", "Ken", "Chunli", "Zangief", "Dhalsim"};
        std::vector<int> offsetnum = {0, 0};
        std::vector<int> offset = {430, 375, 360, 405, 430, 370, 370, 370};
        float P1blood = 100.0f;
        float P2blood = 100.0f;
        std::shared_ptr<ImageSpace> P1name_image;
        std::shared_ptr<ImageSpace> P2name_image;
        std::vector<int> timer = {0, 0};
        std::vector<std::shared_ptr<ImageSpace>> AllPictures;
    public:
        UI();
        void Init(std::shared_ptr<Fighter> p1, std::shared_ptr<Fighter> p2);
        void RoundStart(int round);
        void Update();
        void DrawUI();
        void JudgeWinCount(int PlayerWinCounter,int EnemyWinCounter);
        float GetTime() const;
        bool GetRoundStartIsEnd() const {return RoundStartIsEnd;};
        State GetState() const {return currentState;};
        void ChangeState(State state)  {currentState=state;};
    };
}

#endif //BLOODSTICK_HPP