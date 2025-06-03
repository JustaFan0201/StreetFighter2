//
// Created by asus on 2025/6/3.
//

#ifndef ENDINGSCENE_HPP
#define ENDINGSCENE_HPP
#include "Scene.hpp"

namespace Util {
    class EndingScene : public Scene {
    private:
        std::shared_ptr<ImageSpace> Win;

        std::vector<std::shared_ptr<ImageSpace>> AllPictures;//vector of 要被畫的
    public:
        EndingScene();
        void Init(std::shared_ptr<Core::Context> context)override;
        void Update(std::shared_ptr<Core::Context> context) override;
        void Render() override;
    };

}
#endif //ENDINGSCENE_HPP
