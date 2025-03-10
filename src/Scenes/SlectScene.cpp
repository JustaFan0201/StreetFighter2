//
// Created by FanFan on 2025/2/2.
//

#include "Scenes/SlectScene.hpp"
namespace Util {
    SlectScene::SlectScene()= default;
    void SlectScene::Init(std::shared_ptr<Core::Context> context) {
        m_Animation = std::make_shared<AnimationSpace>(
            std::vector<std::string> {
                "../sencepicture/slect/map.png"
            },
            true,
            2000,
            false,
            0
        );
        m_Animation->SetSize({context->GetWindowWidth(),context->GetWindowHeight()});
        //世界地圖
        m_BGM = std::make_shared<BGM>("../music/03 Player Select.mp3");
        m_BGM->SetVolume(20);
        m_BGM->Play(-1);
        //BGM設定
        character_nametag=std::make_shared<ImageSpace>(characters[chooseIndex]->GetNameTag());
        character=std::make_shared<ImageSpace>(characters[chooseIndex]->GetFace());
        character_match_country=std::make_shared<ImageSpace>(characters[chooseIndex]->GetCountry());
        first_player = std::make_shared<ImageSpace>("../sencepicture/slect/1p.png");
        first_player_screen = std::make_shared<ImageSpace>("../sencepicture/slect/1p_screen.png");

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
        //各物件位置
    }

    void SlectScene::Update(std::shared_ptr<Core::Context> context) {
        Transform position = first_player_screen->GetTransform();
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
        //選擇角色
        character_nametag->SetDrawable(std::make_shared<Image>(characters[chooseIndex]->GetNameTag()));//1p Nametag
        character->SetDrawable(std::make_shared<Image>(characters[chooseIndex]->GetFace())); //角色
        character_match_country->SetDrawable(std::make_shared<Image>(characters[chooseIndex]->GetCountry()));//角色的國家
        character_match_country->SetTransform(characters[chooseIndex]->GetCountryPosition());
        first_player_screen->SetTransform(position);
        //更新位置
    }

    void SlectScene::Render() {
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