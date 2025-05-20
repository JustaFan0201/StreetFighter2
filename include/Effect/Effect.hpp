//
// Created by asus on 2025/5/20.
//

#ifndef EFFECT_HPP
#define EFFECT_HPP
#include <string>
#include <AnimationSpace.hpp>
namespace Util {
    class Effect {
    public:
        Effect(std::string name): Name(name){}
        virtual ~Effect() = default;
        void Init(glm::vec2 position);
        void Update();
        void Draw(glm::vec2 cameraPos);
        std::string GetName(){return Name;};
        void AnimationInit(int picture_number, int duration);
        [[nodiscard]] bool IsAnimationEnd() const {return animation->IsAnimationEnds();}
        [[nodiscard]] bool IsEnd() const{return EffectIsEnd;}
    protected:
        std::string Name;
        std::shared_ptr<AnimationSpace> animation;
        bool EffectIsEnd=false;
    };
}

#endif //EFFECT_HPP
