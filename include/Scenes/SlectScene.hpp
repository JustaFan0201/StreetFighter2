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
        unsigned long start = Time::GetElapsedTimeMs();
        std::shared_ptr<SFX> soundEffect_slect = std::make_shared<SFX>("../voice/01 Select Screen & World Map/SFII_02 - Move Cursor.wav");
        std::shared_ptr<SFX> soundEffect_enter = std::make_shared<SFX>("../voice/01 Select Screen & World Map/SFII_03 - Selection.wav");

        std::shared_ptr<ImageSpace> character=std::make_shared<ImageSpace>("../sencepicture/slect/ryu_face.png");//角色
        std::shared_ptr<ImageSpace> character_match_country;
        std::shared_ptr<ImageSpace> first_player = std::make_shared<ImageSpace>("../sencepicture/slect/1p.png");//1p
        std::shared_ptr<ImageSpace> first_player_screen = std::make_shared<ImageSpace>("../sencepicture/slect/1p_screen.png");//1p框框

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

        std::vector<std::shared_ptr<ImageSpace>> countries = {
            std::make_shared<ImageSpace>("../sencepicture/slect/japan.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/japan.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/brazil.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/usa.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/usa.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/china.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/ussr.png"),
            std::make_shared<ImageSpace>("../sencepicture/slect/india.png")
        };
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
        std::vector<Transform> country_position = {
           {{14,90},0,{1,1}},
           {{28, 168},0,{1,1}},
           {{323, 23},0,{1,1}},
           {{350, 140},0,{1,1}},
           {{338, 245},0,{1,1}},
           {{-113, 193},0,{1,1}},
           {{-251, 217},0,{1,1}},
           {{-228, 97},0,{1,1}}
        };
        int chooseIndex = 0;
        public:
        SlectScene();
        void Init() override;   // 初始化
        void Update() override; // 更新場景
        void Render() override; // 渲染圖片
    };
}
#endif //SLECTSCENE_HPP
