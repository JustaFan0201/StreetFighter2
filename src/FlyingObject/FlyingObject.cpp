//
// Created by FanFan on 2025/4/5.
//

#include "FlyingObject/FlyingObject.hpp"
namespace Util {
    std::vector<std::string> FlyingObect::ActionInit(int picture_number, std::string Action) {
        std::vector<std::string> Allframe;
        for (int i = 1; i <= picture_number; i++) {
            std::string num = std::to_string(i);
            std::string filename = RESOURCE_DIR"/ScenePicture/FlyingObject/"+ GetName() +"/"+ Action +"/frame (" + num +").png";
            Allframe.push_back(filename);
        }
        return Allframe;
    }
    void FlyingObect::SetAnimation(FlyingObjectState action,std::vector<int> intervals,std::vector<glm::vec2> offsets) {
        if (animations.find(action) != animations.end()) {
            animationNow->SetDrawable(std::make_shared<Animation>(animations[action], true, 60, false));
            animationNow->SetFrameIntervals(intervals);
            animationNow->Setoffset(offsets);
        }
    }
    void FlyingObect::ChangeState(FlyingObjectState newState) {
        if (currentState != newState) {
            currentState = newState;
            SetAnimation(currentState,frames[currentState],GetCurrentOffsets());
        }
    }
    void  FlyingObect::Movement() {
        glm::vec2 position={animationNow->GetTransform().translation.x+direction*velocity.x*Time::GetDeltaTimeMs()/1000,
            animationNow->GetTransform().translation.y};
        if (position.x<-640 || position.x>640) {
            ObjectIsEnd=true;
        }
        animationNow->SetDrawData(
            {position, 0, {direction, 1}},
            animationNow->GetOriginalSize()*glm::vec2 {3,3},
            3.0f
        );
    }
}

