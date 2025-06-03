//
// Created by FanFan on 2025/1/27.
//

// StartScene.hpp
#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP

#include "Scene.hpp"
namespace Util {
    enum class StartSceneState {
        Null,
        Start,
        WaitForSlect,
        WaitForEnd
    };
    class StartScene : public Scene {
    private:
        std::shared_ptr<SFX> soundEffect = std::make_shared<Util::SFX>(RESOURCE_DIR"/voice/01 Select Screen & World Map/SFII_01 - Mode Select.wav");

        std::shared_ptr<ImageSpace> storymode;
        std::shared_ptr<ImageSpace> battlemode;
        StartSceneState m_state = StartSceneState::Null;
    public:
        StartScene();
        void Init(std::shared_ptr<Core::Context> context) override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
    };

} // namespace Util

#endif /* STARTSCENE_HPP */
