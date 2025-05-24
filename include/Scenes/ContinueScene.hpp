//
// Created by asus on 2025/5/24.
//

#ifndef CONTINUESCENE_HPP
#define CONTINUESCENE_HPP
#include "Scene.hpp"

namespace Util {
    enum class ChooseResult {
        Null,
        GameOver,
        Continue
    };
    enum class ContinueSceneState {
        Null,
        Start,
        WaitForEnd,
        End
    };
    class ContinueScene : public Scene {
    private:
        std::shared_ptr<Fighter> player;
        std::shared_ptr<SFX> countsound;
        std::shared_ptr<SFX> continuesound;
        std::shared_ptr<ImageSpace> player_face;//1p角色臉
        std::shared_ptr<ImageSpace> time_picture;

        int timer=10;
        ContinueSceneState currentstate=ContinueSceneState::Null;
        ChooseResult Result=ChooseResult::Null;
        std::vector<std::shared_ptr<ImageSpace>> AllPictures;//vector of 要被畫的
    public:
        ContinueScene(const std::shared_ptr<Fighter> &player):
        player(player){}
        void Init(std::shared_ptr<Core::Context> context)override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
        ChooseResult GetChooseResult() const {return Result;}
    };

} // namespace Util
#endif //CONTINUESCENE_HPP
