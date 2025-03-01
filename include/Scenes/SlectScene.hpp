//
// Created by FanFan on 2025/2/2.
//

#ifndef SLECTSCENE_HPP
#define SLECTSCENE_HPP
#include "Scenes/Scene.hpp"

namespace Util {
    class SlectScene : public Scene {
        private:
        bool m_WaitingForEnter=true;
        std::shared_ptr<SFX> soundEffect_slect = std::make_shared<SFX>("../voice/01 Select Screen & World Map/SFII_02 - Move Cursor.wav");
        std::shared_ptr<SFX> soundEffect_enter = std::make_shared<SFX>("../voice/01 Select Screen & World Map/SFII_03 - Selection.wav");

        std::vector<std::shared_ptr<Fighter>> characters = {
            std::make_shared<Ryu>(),    // 指向子類 Ryu
            std::make_shared<Honda>(),  // 指向子類 Honda
            std::make_shared<Blanka>(), // 指向子類 Blanka
            std::make_shared<Guile>(),  // 指向子類 Guile
            std::make_shared<Ken>(),    // 指向子類 Ken
            std::make_shared<Chunli>(), // 指向子類 Chunli
            std::make_shared<Zangief>(),// 指向子類 Zangief
            std::make_shared<Dhalsim>() // 指向子類 Dhalsim
        };

        std::shared_ptr<ImageSpace> character=characters[0]->GetFace();//角色
        std::shared_ptr<ImageSpace> character_match_country=characters[0]->GetCountry();
        std::shared_ptr<ImageSpace> character_nametag=characters[0]->GetNameTag();
        std::shared_ptr<ImageSpace> first_player = std::make_shared<ImageSpace>("../sencepicture/slect/1p.png");//1p
        std::shared_ptr<ImageSpace> first_player_screen = std::make_shared<ImageSpace>("../sencepicture/slect/1p_screen.png");//1p框框

        std::vector<std::shared_ptr<ImageSpace>> AllPictures={};

        std::vector<std::shared_ptr<ImageSpace>> countries_dark = {
                std::make_shared<ImageSpace>("../sencepicture/slect/japan_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/japan_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/brazil_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/usa_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/usa_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/china_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/ussr_dark.png"),
               std::make_shared<ImageSpace>("../sencepicture/slect/india_dark.png")
        };
        int chooseIndex = 0;
        public:
        SlectScene();
        void Init() override;   // 初始化
        void Update() override; // 更新場景
        void Render() override; // 渲染圖片
        std::shared_ptr<Fighter> GetPlayerCharacter(){return characters[chooseIndex];}
    };
}
#endif //SLECTSCENE_HPP
