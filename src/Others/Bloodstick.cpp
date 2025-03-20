//
// Created by Gs0n on 25-3-10.
//

#include "Others/Bloodstick.hpp"

namespace Util {
    Bloodstick::Bloodstick() {
        bloodback_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodBack.png");
        ko_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/ko.png");
        bloodfrontPlayer_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodFront.png");
        bloodfrontEnemy_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/BloodFront.png");
        playername_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/Ken.png");
        enemyname_image =  std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/Ken.png");
    }

    void Bloodstick::Update(std::string p1, std::string p2) {
        this -> player = p1;
        this -> enemy = p2;
        playername_image = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/" + player + ".png");
        enemyname_image =  std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Battle/Bloodstick/"+ enemy +".png");
        for (int i=0; i<8; i++) {
            if (player == namebox[i]) offsetnum[0] = i;
            if (enemy == namebox[i]) offsetnum[1] = i;
        }
        if (Input::IsKeyPressed(Keycode::DOWN) && playerblood > 0) {
           playerblood -= 1;
        }
        else if (Input::IsKeyPressed(Keycode::UP) && playerblood < 100) {
            playerblood += 1;
        }
        if (Input::IsKeyPressed(Keycode::LEFT) && enemyblood > 0) {
            enemyblood -= 1;
        }
        else if (Input::IsKeyPressed(Keycode::RIGHT) && enemyblood < 100) {
            enemyblood += 1;
        }
    }

    void Bloodstick::DrawBloodstick(){
        //left = -51
        bloodfrontPlayer_image->SetDrawData({{-(227 * (playerblood / 100)) - 51.2 , 276}, 0, {1, 1}}, {bloodfrontPlayer_image->GetScaledSize().x *3.15 * (playerblood / 100) , bloodfrontPlayer_image->GetScaledSize().y * 3.15}, 2.0f);
        bloodfrontPlayer_image->custom_Draw();
        bloodfrontEnemy_image->SetDrawData({{(227 * (enemyblood / 100)) + 51.2 , 276}, 0, {1, 1}}, {bloodfrontEnemy_image->GetScaledSize().x *3.15 * (enemyblood / 100) , bloodfrontEnemy_image->GetScaledSize().y * 3.15}, 2.0f);
        bloodfrontEnemy_image->custom_Draw();

        ko_image->SetDrawData({{0, 276}, 0, {1, 1}}, {ko_image->GetScaledSize().x * 3.2, ko_image->GetScaledSize().y * 3.5}, 2.0f);
        ko_image->custom_Draw();
        bloodback_image->SetDrawData({{0, 280}, 0, {1, 1}}, {bloodback_image->GetScaledSize().x * 3.151, bloodback_image->GetScaledSize().y * 3.15}, 2.0f);
        bloodback_image->custom_Draw();

        playername_image->SetDrawData({{- offset[offsetnum[0]], 235}, 0, {1, 1}}, {playername_image->GetScaledSize().x * 4, playername_image->GetScaledSize().y * 4}, 2.0f);
        playername_image->custom_Draw();

        enemyname_image->SetDrawData({{offset[offsetnum[1]], 235}, 0, {1, 1}}, {enemyname_image->GetScaledSize().x * 4, enemyname_image->GetScaledSize().y * 4}, 2.0f);
        enemyname_image->custom_Draw();

    }
}




