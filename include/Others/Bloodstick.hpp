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
        std::shared_ptr<ImageSpace> bloodback_image;
        std::shared_ptr<ImageSpace> ko_image;
        std::shared_ptr<ImageSpace> bloodfrontP1_image;
        std::shared_ptr<ImageSpace> bloodfrontP2_image;
        std::shared_ptr<ImageSpace> timerTens_image;
        std::shared_ptr<ImageSpace> timerUnits_image;

        float start_time = Time::GetElapsedTimeMs();
        float now_time = Time::GetElapsedTimeMs();
        std::string P1;
        std::string P2;
        std::vector<std::string> namebox = {"Ryu", "Honda", "Blanka", "Guile", "Ken", "Chunli", "Zangief", "Dhalsim"};
        std::vector<int> offsetnum = {0, 0};
        std::vector<int> offset = {430, 375, 360, 405, 430, 370, 360, 360};
        float P1blood = 100.0f;
        float P2blood = 100.0f;
        std::shared_ptr<ImageSpace> P1name_image;
        std::shared_ptr<ImageSpace> P2name_image;
        std::vector<int> timer = {0, 0};
        std::vector<std::shared_ptr<ImageSpace>> AllPictures;

    public:
        Bloodstick();
        void Init(std::string p1, std::string p2);
        void Update();
        void DrawBloodstick();

    };
}

#endif //BLOODSTICK_HPP