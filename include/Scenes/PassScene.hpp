//
// Created by FanFan on 2025/2/28.
//

#ifndef PASSSCENE_HPP
#define PASSSCENE_HPP
#include "Scene.hpp"
namespace Util {
    class PassScene : public Scene {
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;

        std::shared_ptr<ImageSpace> player_face=player->GetFace();
        std::shared_ptr<ImageSpace> player_nametag=player->GetNameTag();
        std::shared_ptr<ImageSpace> enemy_face=enemy->GetFace();
        std::shared_ptr<ImageSpace> enemy_nametag=enemy->GetNameTag();

        std::shared_ptr<ImageSpace> vs=std::make_shared<ImageSpace>("../sencepicture/Pass/PassScene.png");
        std::vector<std::shared_ptr<ImageSpace>> AllPictures;
    public:
        PassScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy):player(player),enemy(enemy){}
        void Init() override;   // 初始化
        void Update() override; // 更新場景
        void Render() override; // 渲染圖片
    };

}
#endif //PASSSCENE_HPP
