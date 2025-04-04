//
// Created by Gs0n on 25-3-10.
//

#include "Others/Bloodstick.hpp"

namespace Util {
    Bloodstick::Bloodstick() {
        bloodback_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodBack.png");
        ko_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/ko.png");
        bloodfrontP1_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodFront.png");
        bloodfrontP2_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodFront.png");
        P1name_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/Ken.png");
        P2name_image =  std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/Ken.png");
        timerTens_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/9.png");
        timerUnits_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/9.png");
        fight_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/Fight.png");
        round_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/Round.png");
        roundnum_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/1.png");
    }

    void Bloodstick::Init(std::shared_ptr<Fighter> p1, std::shared_ptr<Fighter> p2) {
        P1 = p1;
        P2 = p2;
        P1name_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + P1->GetName()+ ".png");
        P2name_image =  std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/"+ P2->GetName() +".png");
        for (int i=0; i<8; i++) {
            if (P1->GetName()== namebox[i]) offsetnum[0] = i;
            if (P2->GetName() == namebox[i]) offsetnum[1] = i;
        }
        ko_image->SetDrawData({{0, 276}, 0, {1, 1}}, {ko_image->GetScaledSize().x * 3.2, ko_image->GetScaledSize().y * 3.5}, 2.0f);
        bloodback_image->SetDrawData({{0, 280}, 0, {1, 1}}, {bloodback_image->GetScaledSize().x * 3.151, bloodback_image->GetScaledSize().y * 3.15}, 2.0f);
        P1name_image->SetDrawData({{- offset[offsetnum[0]], 235}, 0, {1, 1}}, {P1name_image->GetScaledSize().x * 4, P1name_image->GetScaledSize().y * 4}, 2.0f);
        P2name_image->SetDrawData({{offset[offsetnum[1]], 235}, 0, {1, 1}}, {P2name_image->GetScaledSize().x * 4, P2name_image->GetScaledSize().y * 4}, 2.0f);
    }

    void Bloodstick::Update() {
        now_time = Time::GetElapsedTimeMs();
        if ((now_time - start_time) / 1000 < 1.5) {
            round_image->SetDrawData({{-30, 100}, 0, {1, 1}}, {round_image->GetScaledSize().x * 3.8, round_image->GetScaledSize().y * 3.8}, 7.0f);
            roundnum_image->SetDrawData({{118, 100}, 0, {1, 1}}, {roundnum_image->GetScaledSize().x * 5, roundnum_image->GetScaledSize().y * 5.7}, 7.0f);
        }
        else if ((now_time - start_time) / 1000 < 3) {
            fight_image->SetDrawData({{0, 100}, 0, {1, 1}}, {fight_image->GetScaledSize().x * 4, fight_image->GetScaledSize().y * 4.2}, 7.0f);
        }
        else if ((now_time - start_time) / 1000  + 3 <= 100){
            timer[0] = (99 - int((now_time - start_time) / 1000) + 3) / 10 ;
            timer[1] = (99 - int((now_time - start_time) / 1000) + 3)  % 10 ;
            timerTens_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + std::to_string(timer[0]) + ".png");
            timerUnits_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + std::to_string(timer[1]) + ".png");
        }
        P1blood = P1->GetHP();
        P2blood = P2->GetHP();
        if(P1blood<0) {P1blood = 0;}
        if(P2blood<0) {P2blood = 0;}

        //left = -51
        timerTens_image->SetDrawData({{-20 , 220}, 0, {1, 1}}, {timerTens_image->GetScaledSize().x *3.3 , timerTens_image->GetScaledSize().y * 3.3}, 2.0f);
        timerUnits_image->SetDrawData({{20 , 220}, 0, {1, 1}}, {timerUnits_image->GetScaledSize().x *3.3 , timerUnits_image->GetScaledSize().y * 3.3}, 2.0f);
        bloodfrontP1_image->SetDrawData({{-((227 * (P1blood / 100)) + 51.2), 276}, 0, {1, 1}}, {bloodfrontP1_image->GetScaledSize().x *3.15 * (P1blood / 100) , bloodfrontP1_image->GetScaledSize().y * 3.15}, 2.0f);
        bloodfrontP2_image->SetDrawData({{(227 * (P2blood / 100)) + 51.2 , 276}, 0, {1, 1}}, {bloodfrontP2_image->GetScaledSize().x *3.15 * (P2blood / 100) , bloodfrontP2_image->GetScaledSize().y * 3.15}, 2.0f);
    }

    void Bloodstick::DrawBloodstick() {
        AllPictures={timerTens_image,timerUnits_image,bloodfrontP1_image,bloodfrontP2_image,ko_image,bloodback_image,P1name_image,P2name_image};
        for(const auto& i:AllPictures) {
            i->custom_Draw();
        }
    }
    float Bloodstick::GetTime() {
        return now_time - start_time;
    }

}