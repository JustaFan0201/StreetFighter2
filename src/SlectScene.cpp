//
// Created by FanFan on 2025/2/2.
//

#include "SlectScene.hpp"
namespace Util {
    SlectScene::SlectScene(){}
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

        character_match_country=countries[0];

        character = std::make_shared<ImageSpace>("../sencepicture/slect/ryu_face.png");//角色
        character->SetDraw({{-420, -180},0,{1,1}},
                {288, 345},
                1.0f);


        first_player = std::make_shared<ImageSpace>("../sencepicture/slect/1p.png");//1p
        first_player->SetDraw({{-420, 20},0,{1,1}},
                {162, 84},
                1.0f);

        first_player_screen = std::make_shared<ImageSpace>("../sencepicture/slect/1p_screen.png");//1p框框
        first_player_screen->SetDraw({{-160, -150},0,{1,1}},
                {120, 144},
                1.0f);

        int j = 0;  // 定義並初始化 j
        for (auto i : countries_dark) {
            i->SetDraw(country_position[j],
                       {72, 58},
                       1.0f);
            j++;
        }
    }

    void SlectScene::Update() {
        if (Input::IsKeyPressed(Keycode::MOUSE_LB)) {
            glm::vec2 mousePos = Input::GetCursorPosition(); // 取得滑鼠座標
            std::cout << "Mouse Clicked at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
        }
        Transform position = {{first_player_screen->GetTransform().translation.x,first_player_screen->GetTransform().translation.y}
            ,0
            ,{1,1}};
        int row = chooseIndex / 4;
        int col = chooseIndex % 4;

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
        }
        character_match_country=countries[chooseIndex];//角色的國家
        character_match_country->SetDraw(country_position[chooseIndex],
                    {72, 58},
                    2.0f);

        character = characters[chooseIndex]; //角色
        character->SetDraw({{-420, -180},0,{1,1}},
                    {288, 345},
                    1.0f);
        first_player_screen->SetDraw(position,
                    {120, 144},
                    1.0f);
    }

    void SlectScene::Render() {
        // 在這裡渲染動畫的當前幀
        m_Animation->custom_Draw();
        character->custom_Draw();
        first_player->custom_Draw();
        first_player_screen->custom_Draw();
        for(auto i:countries_dark) {
            i->custom_Draw();
        }
        character_match_country->custom_Draw();
    }

}