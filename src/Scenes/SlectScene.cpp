//
// Created by FanFan on 2025/2/2.
//

#include "Scenes/SlectScene.hpp"

#include "Scenes/SceneManager.hpp"

namespace Util {
    void SlectScene::Init(std::shared_ptr<Core::Context> context) {
        player1data.chooseIndex=0;
        player2data.chooseIndex=3;
        player1data.number=1;
        player2data.number=2;
        player1data.direction=FighterDirection::Left;
        player2data.direction=FighterDirection::Right;
        m_Animation = std::make_shared<AnimationSpace>(
            std::vector<std::string> {
                RESOURCE_DIR"/ScenePicture/slect/map.png"
            },
            true,
            2000,
            false,
            0
        );
        BossSlectable();
        m_Animation->SetSize({context->GetWindowWidth(),context->GetWindowHeight()});
        //世界地圖
        m_BGM = std::make_shared<BGM>(RESOURCE_DIR"/music/03 Player Select.mp3");
        m_BGM->SetVolume(20);
        m_BGM->Play(-1);
        //BGM設定
        player1data.controller=std::make_shared<Controller>(PlayerType::Player1);
        PlayerDataInit(player1data);
        if(mode==ModeType::Story){player2data.Ready=true;}
        if(mode==ModeType::Battle) {
            player2data.controller=std::make_shared<Controller>(PlayerType::Player2);
            PlayerDataInit(player2data);
        }
        int j = 0;
        for(const auto& [key,fighter]:characters) {
            std::shared_ptr<Fighter> currentFighter=fighter();
            countries_dark.push_back(std::make_shared<ImageSpace>(currentFighter->GetCountryDark()));
            countries_dark[j]->SetDrawData(currentFighter->GetCountryPosition(),
                       {72, 58},
                       3.0f);
            j++;
        }
    }

    void SlectScene::Update(std::shared_ptr<Core::Context> context) {
        PlayerDataUpdate(player1data);
        if(mode==ModeType::Battle){PlayerDataUpdate(player2data);}
        if(player1data.Ready&&player2data.Ready&&(GetPassedTime()>600)) {
            SenseEnd=true;
        }
    }

    void SlectScene::Render() {
        m_Animation->custom_Draw();
        Boss_Icon->custom_Draw();
        PlayerDataRender(player1data);
        if(mode==ModeType::Battle){PlayerDataRender(player2data);}
        for(const auto& i:countries_dark) {
            i->custom_Draw();
        }
    }
    void SlectScene::PlayerDataInit(PlayerData &playerdata) const {
        FighterList chosen = index_to_enum[playerdata.chooseIndex];
        playerdata.player = characters.at(chosen)();
        playerdata.controller->SetState(ControllerState::Active);
        playerdata.character_nametag=std::make_shared<ImageSpace>(playerdata.player->GetNameTag());
        playerdata.character=std::make_shared<ImageSpace>(playerdata.player->GetFace());
        playerdata.character_match_country=std::make_shared<ImageSpace>(playerdata.player->GetCountry());
        playerdata.player_number = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/"+std::to_string(playerdata.number)+"p.png");
        playerdata.player_number_screen = std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/"+std::to_string(playerdata.number)+"p_screen.png");

        playerdata.character_nametag->SetDrawData({{-480*static_cast<int>(playerdata.direction), -320},0,{1,1}},
                    {288,63},
                    3.0f);
        playerdata.character->SetDrawData({{-480*static_cast<int>(playerdata.direction), -150},0,{1*static_cast<int>(playerdata.direction),1}},
                    {288, 288},
                    3.0f);
        playerdata.player_number->SetDrawData({{-480*static_cast<int>(playerdata.direction), 20},0,{1,1}},
                {162, 84},
                3.0f);
        playerdata.player_number_screen->SetDrawData(playerdata.player->GetFacePosition(),
                {120, 144},
                3.0f);
        playerdata.character_match_country->SetDrawData(playerdata.player->GetCountryPosition(),
                {72, 58},
                4.0f);
    }
    void SlectScene::PlayerDataUpdate(PlayerData &playerdata) {
        const int maxIndex = PassedGame ? 9 : 8;  // 可選角色總數
        if (!SenseEnd) {
            if (playerdata.controller->IsKeyDown(Keys::UP)) {
                // index 4~7 -> 上移 -4；index 8 -> 無法上移
                if (playerdata.chooseIndex >= 4 && playerdata.chooseIndex < 8) {
                    playerdata.chooseIndex -= 4;
                    soundEffect_slect->Play(0);
                }
            }
            if (playerdata.controller->IsKeyDown(Keys::DOWN)) {
                // index 0~3 -> 下移 +4；index 4~7 -> 無效；index 8 -> 無效
                if (playerdata.chooseIndex < 4 && playerdata.chooseIndex + 4 < maxIndex) {
                    playerdata.chooseIndex += 4;
                    soundEffect_slect->Play(0);
                }
            }
            if (playerdata.controller->IsKeyDown(Keys::LEFT)) {
                if (playerdata.chooseIndex % 4 != 0) {
                    playerdata.chooseIndex--;
                    soundEffect_slect->Play(0);
                } else if (playerdata.chooseIndex == 8) {
                    // 從 index 8（右上角）往左，移到 index 3
                    playerdata.chooseIndex = 3;
                    soundEffect_slect->Play(0);
                }
            }
            if (playerdata.controller->IsKeyDown(Keys::RIGHT)) {
                if (playerdata.chooseIndex < maxIndex - 1) {
                    // index 0~2 -> 一般右移
                    if (playerdata.chooseIndex % 4 < 3) {
                        playerdata.chooseIndex++;
                        soundEffect_slect->Play(0);
                    } else if (PassedGame && (playerdata.chooseIndex == 3 || playerdata.chooseIndex == 7)) {
                        // 從 index 3 移到 index 8（特別角色）
                        playerdata.chooseIndex = 8;
                        soundEffect_slect->Play(0);
                    }
                }
            }
            if (playerdata.controller->IsKeyDown(Keys::ENTER)) {
                playerdata.controller->SetState(ControllerState::Pause);
                playerdata.Ready = true;
                soundEffect_enter->Play(0);
                start_time = Time::GetElapsedTimeMs();
            }
        }
        FighterList chosen = index_to_enum[playerdata.chooseIndex];
        playerdata.player = characters.at(chosen)();
        //選擇角色
        playerdata.character_nametag->SetDrawable(std::make_shared<Image>(playerdata.player->GetNameTag()));//1p Nametag
        playerdata.character->SetDrawable(std::make_shared<Image>(playerdata.player->GetFace())); //角色
        playerdata.character_match_country->SetDrawable(std::make_shared<Image>(playerdata.player->GetCountry()));//角色的國家
        playerdata.character_match_country->SetTransform(playerdata.player->GetCountryPosition());
        playerdata.player_number_screen->SetTransform(playerdata.player->GetFacePosition());
        //更新位置
    }
    void SlectScene::PlayerDataRender(PlayerData &playerdata) {
        playerdata.AllPictures={playerdata.character,playerdata.character_match_country,
            playerdata.player_number,playerdata.player_number_screen,playerdata.character_nametag};
        for(const auto& i:playerdata.AllPictures) {
            i->custom_Draw();
        }
    }
}
