//
// Created by USER on 2025/5/23.
//

#ifndef WINLOSSSCENE_HPP
#define WINLOSSSCENE_HPP
#include "Scene.hpp"
namespace Util {
    class WinLossScene : public Scene {
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<Fighter> enemy;
        FinalResult result=FinalResult::Null;

        std::shared_ptr<ImageSpace> player_face;//1p角色臉
        std::shared_ptr<ImageSpace> enemy_face;//2p角色臉
        std::shared_ptr<ImageSpace> winword;

        std::vector<std::shared_ptr<ImageSpace>> AllPictures;//vector of 要被畫的
    public:
        WinLossScene(const std::shared_ptr<Fighter> &player, const std::shared_ptr<Fighter> &enemy,FinalResult result):
        player(player),enemy(enemy),result(result){}
        void Init(std::shared_ptr<Core::Context> context)override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
    };

} // namespace Util
#endif //WINLOSSSCENE_HPP
