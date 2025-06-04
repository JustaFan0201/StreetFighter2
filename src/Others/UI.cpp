//
// Created by Gs0n on 25-3-10.
//

#include "Others/UI.hpp"
namespace Util {
    UI::UI() {
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
        PlayerWinCountImage = {
            std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/WinCount.png"),
            std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/WinCount.png")
        };
        EnemyWinCountImage = {
            std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/WinCount.png"),
            std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/WinCount.png")
        };
    }
    void UI::JudgeWinCount(int PlayerWinCounter,int EnemyWinCounter) {
        this->PlayerWinCounter=PlayerWinCounter;
        this->EnemyWinCounter=EnemyWinCounter;
        if(PlayerWinCounter==1) {
            PlayerWinCountImage[0]->SetVisible(true);
            PlayerWinCountImage[1]->SetVisible(false);
        }
        else if(PlayerWinCounter==2) {
            PlayerWinCountImage[0]->SetVisible(true);
            PlayerWinCountImage[1]->SetVisible(true);
        }
        else {
            PlayerWinCountImage[0]->SetVisible(false);
            PlayerWinCountImage[1]->SetVisible(false);
        }
        if(EnemyWinCounter==1) {
            EnemyWinCountImage[0]->SetVisible(true);
            EnemyWinCountImage[1]->SetVisible(false);
        }
        else if(EnemyWinCounter==2) {
            EnemyWinCountImage[0]->SetVisible(true);
            EnemyWinCountImage[1]->SetVisible(true);
        }
        else {
            EnemyWinCountImage[0]->SetVisible(false);
            EnemyWinCountImage[1]->SetVisible(false);
        }
    }
    void UI::Init(std::shared_ptr<Fighter> p1, std::shared_ptr<Fighter> p2) {
        PlayerWinCountImage[0]->SetDrawData({{-595,275},0,{1, 1}},{PlayerWinCountImage[0]->GetScaledSize()*glm::vec2(3,3)},10.0f);
        PlayerWinCountImage[1]->SetDrawData({{-540,275},0,{1, 1}},{PlayerWinCountImage[1]->GetScaledSize()*glm::vec2(3,3)},10.0f);
        EnemyWinCountImage[0]->SetDrawData({{595,275},0,{1, 1}},{EnemyWinCountImage[0]->GetScaledSize()*glm::vec2(3,3)},10.0f);
        EnemyWinCountImage[1]->SetDrawData({{540,275},0,{1, 1}},{EnemyWinCountImage[1]->GetScaledSize()*glm::vec2(3,3)},10.0f);

        RoundStartIsEnd=false;
        start_time=Time::GetElapsedTimeMs();
        currentState=State::Round;
        P1 = p1;
        P2 = p2;
        P1blood = p1->GetHP();
        P2blood = p2->GetHP();
        bloodfrontP1_image->SetDrawData({{-((227 * (P1blood / 100)) + 51.2), 276}, 0, {1, 1}}, {bloodfrontP1_image->GetScaledSize().x *3.15 * (P1blood / 100) , bloodfrontP1_image->GetScaledSize().y * 3.15}, 10.0f);
        bloodfrontP2_image->SetDrawData({{(227 * (P2blood / 100)) + 51.2 , 276}, 0, {1, 1}}, {bloodfrontP2_image->GetScaledSize().x *3.15 * (P2blood / 100) , bloodfrontP2_image->GetScaledSize().y * 3.15}, 10.0f);

        timerTens_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/9.png");
        timerUnits_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/9.png");
        timerTens_image->SetDrawData({{-20 , 220}, 0, {1, 1}}, {timerTens_image->GetScaledSize().x *3.3 , timerTens_image->GetScaledSize().y * 3.3}, 10.0f);
        timerUnits_image->SetDrawData({{20 , 220}, 0, {1, 1}}, {timerUnits_image->GetScaledSize().x *3.3 , timerUnits_image->GetScaledSize().y * 3.3}, 10.0f);

        P1name_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + P1->GetName()+ ".png");
        P2name_image =  std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/"+ P2->GetName() +".png");
        for (int i=0; i<offset.size(); i++) {
            if (P1->GetName()== namebox[i]) offsetnum[0] = i;
            if (P2->GetName() == namebox[i]) offsetnum[1] = i;
        }
        ko_image->SetDrawData({{0, 276}, 0, {1, 1}}, {ko_image->GetScaledSize().x * 3.2, ko_image->GetScaledSize().y * 3.5}, 10.0f);
        bloodback_image->SetDrawData({{0, 280}, 0, {1, 1}}, {bloodback_image->GetScaledSize().x * 3.151, bloodback_image->GetScaledSize().y * 3.15}, 10.0f);
        P1name_image->SetDrawData({{- offset[offsetnum[0]], 235}, 0, {1, 1}}, {P1name_image->GetScaledSize().x * 4, P1name_image->GetScaledSize().y * 4}, 10.0f);
        P2name_image->SetDrawData({{offset[offsetnum[1]], 235}, 0, {1, 1}}, {P2name_image->GetScaledSize().x * 4, P2name_image->GetScaledSize().y * 4}, 10.0f);

        round_image->SetDrawData({{-30, 100}, 0, {1, 1}}, {round_image->GetScaledSize().x * 3.8, round_image->GetScaledSize().y * 3.8}, 10.0f);
        roundnum_image->SetDrawData({{118, 100}, 0, {1, 1}}, {roundnum_image->GetScaledSize().x * 5, roundnum_image->GetScaledSize().y * 5.7}, 10.0f);
        fight_image->SetDrawData({{0, 100}, 0, {1, 1}}, {fight_image->GetScaledSize().x * 4, fight_image->GetScaledSize().y * 4.2}, 10.0f);
    }

    void UI::RoundStart(int round) {
        if(currentState==State::Round) {
            roundnum_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/"+std::to_string(round)+".png");
            roundnum_image->SetDrawData({{118, 100}, 0, {1, 1}}, {roundnum_image->GetScaledSize().x * 5, roundnum_image->GetScaledSize().y * 5.7}, 10.0f);
            round_image->SetDrawData({{-30, 100}, 0, {1, 1}}, {round_image->GetScaledSize().x * 3.8, round_image->GetScaledSize().y * 3.8}, 10.0f);

            soundeffect=std::make_shared<SFX>(RESOURCE_DIR"/voice/02 Fight Announcer/Round"+std::to_string(round)+".wav");
            soundeffect->Play(0);

            roundnum_image->SetVisible(true);
            round_image->SetVisible(true);
            fight_image->SetVisible(false);
            currentState=State::Fight;
        }
        else if(GetTime()>1500&&currentState==State::Fight) {
            soundeffect=std::make_shared<SFX>(RESOURCE_DIR"/voice/02 Fight Announcer/Fight.wav");
            soundeffect->Play(0);

            roundnum_image->SetVisible(false);
            round_image->SetVisible(false);
            fight_image->SetVisible(true);
            currentState=State::FightEnd;
        }
        else if(GetTime()>2500&&currentState==State::FightEnd) {
            roundnum_image->SetVisible(false);
            round_image->SetVisible(false);
            fight_image->SetVisible(false);

            RoundStartIsEnd=true;
            start_time=Time::GetElapsedTimeMs();
            currentState=State::WaitForEnd;
        }
    }

    void UI::Update() {
        if(currentState==State::WaitForEnd) {
            timer[0] = (99 - static_cast<int>(GetTime()) / 1000 ) / 10 ;
            timer[1] = (99 - static_cast<int>(GetTime()) / 1000 ) % 10 ;
            if(timer[0]<0){timer[0]=0;}
            if(timer[1]<0){timer[1]=0;}
            if(timer[0]==0&&timer[1]==0){currentState=State::TimeOver;}
        }
        if (Input::IsKeyDown(Keycode::L)) {currentState=State::TimeOver;}

        timerTens_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + std::to_string(timer[0]) + ".png");
        timerUnits_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + std::to_string(timer[1]) + ".png");

        P1blood = P1->GetHP();
        P2blood = P2->GetHP();
        if(P1blood<0) {P1blood = 0;}
        if(P2blood<0) {P2blood = 0;}

        //left = -51
        timerTens_image->SetDrawData({{-20 , 220}, 0, {1, 1}}, {timerTens_image->GetScaledSize().x *3.3 , timerTens_image->GetScaledSize().y * 3.3}, 10.0f);
        timerUnits_image->SetDrawData({{20 , 220}, 0, {1, 1}}, {timerUnits_image->GetScaledSize().x *3.3 , timerUnits_image->GetScaledSize().y * 3.3}, 10.0f);
        bloodfrontP1_image->SetDrawData({{-((227 * (P1blood / 100)) + 51.2), 276}, 0, {1, 1}}, {bloodfrontP1_image->GetScaledSize().x *3.15 * (P1blood / 100) , bloodfrontP1_image->GetScaledSize().y * 3.15}, 10.0f);
        bloodfrontP2_image->SetDrawData({{(227 * (P2blood / 100)) + 51.2 , 276}, 0, {1, 1}}, {bloodfrontP2_image->GetScaledSize().x *3.15 * (P2blood / 100) , bloodfrontP2_image->GetScaledSize().y * 3.15}, 10.0f);
    }

    void UI::DrawUI() {
        AllPictures={timerTens_image,timerUnits_image,
            bloodfrontP1_image,bloodfrontP2_image,
            ko_image,bloodback_image,fight_image,
            P1name_image,P2name_image,
            roundnum_image,round_image,
            PlayerWinCountImage[0],EnemyWinCountImage[0],
            PlayerWinCountImage[1],EnemyWinCountImage[1]
        };
        for(const auto& i:AllPictures) {
            i->custom_Draw();
        }
    }

    float UI::GetTime() const {
        return static_cast<int>(Time::GetElapsedTimeMs() - start_time);
    }

}