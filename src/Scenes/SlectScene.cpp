//
// Created by FanFan on 2025/2/2.
//

#include "Scenes/SlectScene.hpp"
namespace Util {
    SlectScene::SlectScene()= default;
    void SlectScene::Init() {
        m_Animation = std::make_shared<AnimationSpace>(
            std::vector<std::string> {//每一張動畫圖片
                "../sencepicture/slect/map.png"
            },
            true,
            2000,
            false,
            100
        );
        m_Animation->SetFullScreen();
        m_BGM = std::make_shared<BGM>("../music/03 Player Select.mp3");
        m_BGM->SetVolume(20);  // 設定音量
        m_BGM->Play(-1); // 播放
        character_nametag->SetDrawData({{-420, -320},0,{1,1}},
                    {288,63},
                    1.0f);
        character->SetDrawData({{-420, -150},0,{1,1}},
                    {288, 288},
                    1.0f);
        first_player->SetDrawData({{-420, 20},0,{1,1}},
                {162, 84},
                1.0f);
        first_player_screen->SetDrawData({{-160, -150},0,{1,1}},
                {120, 144},
                1.0f);
        character_match_country->SetDrawData(characters[chooseIndex]->GetCountryPosition(),
                {72, 58},
                2.0f);
        int j = 0;
        for (const auto& i : countries_dark) {
            i->SetDrawData(characters[j]->GetCountryPosition(),
                       {72, 58},
                       1.0f);
            j++;
        }
    }

    void SlectScene::Update() {
        /*if (Input::IsKeyPressed(Keycode::MOUSE_LB)) {
            glm::vec2 mousePos = Input::GetCursorPosition(); // 取得滑鼠座標
            std::cout << "Mouse Clicked at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
        }*/
        Transform position = {{first_player_screen->GetTransform().translation.x,first_player_screen->GetTransform().translation.y}
            ,0
            ,{1,1}};
        int row = chooseIndex / 4;
        int col = chooseIndex % 4;
        if (!SenseEnd) {
            if (Input::IsKeyDown(Keycode::W) && row > 0) {
                chooseIndex -= 4;
                position.translation.y += 103;
                soundEffect_slect->Play(0);
            }
            if (Input::IsKeyDown(Keycode::S) && row < 1) {
                chooseIndex += 4;
                position.translation.y -= 103;
                soundEffect_slect->Play(0);
            }
            if (Input::IsKeyDown(Keycode::A) && col > 0) {
                chooseIndex--;
                position.translation.x -= 107;
                soundEffect_slect->Play(0);
            }
            if (Input::IsKeyDown(Keycode::D) && col < 3) {
                chooseIndex++;
                position.translation.x += 107;
                soundEffect_slect->Play(0);
            }
            if (Input::IsKeyDown(Keycode::RETURN)) {
                soundEffect_enter->Play(0);
                SDL_Delay(600);
                SenseEnd = true;
            }
        }
        character_nametag=characters[chooseIndex]->GetNameTag();
        character_nametag->SetDrawData({{-420, -320},0,{1,1}},
                    {288,63},
                    1.0f);
        character = characters[chooseIndex]->GetFace(); //角色
        character->SetDrawData({{-420, -150},0,{1,1}},
                    {288, 288},
                    1.0f);
        character_match_country=characters[chooseIndex]->GetCountry();//角色的國家
        character_match_country->SetDrawData(characters[chooseIndex]->GetCountryPosition(),
                    {72, 58},
                    2.0f);
        first_player_screen->SetTransform(position);
    }

    void SlectScene::Render() {
        // 在這裡渲染動畫的當前幀
        m_Animation->custom_Draw();
        AllPictures={character,character_match_country,first_player,first_player_screen,character_nametag};
        for(const auto& i:AllPictures) {
            i->custom_Draw();
        }
        for(const auto& i:countries_dark) {
            i->custom_Draw();
        }
    }

}