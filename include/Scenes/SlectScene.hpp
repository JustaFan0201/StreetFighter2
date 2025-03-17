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
        //音效 enter跟左右
        std::shared_ptr<SFX> soundEffect_slect = std::make_shared<SFX>(RESOURCE_DIR"/voice/01 Select Screen & World Map/SFII_02 - Move Cursor.wav");
        std::shared_ptr<SFX> soundEffect_enter = std::make_shared<SFX>(RESOURCE_DIR"/voice/01 Select Screen & World Map/SFII_03 - Selection.wav");
        //全部角色vector
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

        std::shared_ptr<ImageSpace> character;//角色
        std::shared_ptr<ImageSpace> character_match_country;//當前角色國家
        std::shared_ptr<ImageSpace> character_nametag;//當前角色Nametag
        std::shared_ptr<ImageSpace> first_player;//1p
        std::shared_ptr<ImageSpace> first_player_screen;//1p框框

        std::vector<std::shared_ptr<ImageSpace>> AllPictures={};//要渲染的圖

        std::vector<std::shared_ptr<ImageSpace>> countries_dark = {
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/japan_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/japan_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/brazil_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/usa_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/usa_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/china_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/ussr_dark.png"),
               std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/slect/india_dark.png")
        };
        int chooseIndex = 0;//0~7 characters角色選擇
        public:
        SlectScene();
        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
        std::shared_ptr<Fighter> GetPlayerCharacter(){return characters[chooseIndex];}//回傳1p玩家角色
    };
}
#endif //SLECTSCENE_HPP
