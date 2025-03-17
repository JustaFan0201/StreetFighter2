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

        std::shared_ptr<ImageSpace> player_face;//1p角色臉
        std::shared_ptr<ImageSpace> player_nametag;//1pNameTag
        std::shared_ptr<ImageSpace> enemy_face;//2p角色臉
        std::shared_ptr<ImageSpace> enemy_nametag;//2pNameTag

        std::shared_ptr<ImageSpace> vs=std::make_shared<ImageSpace>(RESOURCE_DIR"/ScenePicture/Pass/PassScene.png");//vs icon
        std::vector<std::shared_ptr<ImageSpace>> AllPictures;//vector of 要被畫的
    public:
        PassScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy):player(player),enemy(enemy){}
        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
    };

}
#endif //PASSSCENE_HPP
