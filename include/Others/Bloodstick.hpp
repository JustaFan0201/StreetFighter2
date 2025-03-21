//
// Created by Gs0n on 25-3-10.
//

#ifndef BLOODSTICK_HPP
#define BLOODSTICK_HPP

#include <memory>
#include <string>
#include "ImageSpace.hpp"
#include "Util/Transform.hpp"
#include"AnimationSpace.hpp"
#include "Util/Time.hpp"
#include "Scenes/Scene.hpp"
//#include "Fighters/Fighter.hpp"
#include <stdio.h>

namespace Util {
    class Bloodstick {
    private:
        std::string original;
        std::shared_ptr<ImageSpace> bloodback_image;
        std::shared_ptr<ImageSpace> ko_image;
        std::shared_ptr<ImageSpace> bloodfrontPlayer_image;
        std::shared_ptr<ImageSpace> bloodfrontEnemy_image;
        std::shared_ptr<ImageSpace> timerTens_image;
        std::shared_ptr<ImageSpace> timerUnits_image;

        float start_time = Time::GetElapsedTimeMs();
        float now_time = Time::GetElapsedTimeMs();
        std::string player;
        std::string enemy;
        std::vector<std::string> namebox = {"Ryu", "Honda", "Blanka", "Guile", "Ken", "Chunli", "Zangief", "Dhalsim"};
        std::vector<int> offsetnum = {0, 0};
        std::vector<int> offset = {430, 375, 360, 405, 430, 370, 360, 360};
        float playerblood = 100;
        float enemyblood = 100;
        std::shared_ptr<ImageSpace> playername_image;
        std::shared_ptr<ImageSpace> enemyname_image;
        std::vector<int> timer = {0,0};

    public:
        Bloodstick();
        void Update(std::string p1, std::string p2);
        void DrawBloodstick();
    };
}

#endif //BLOODSTICK_HPP