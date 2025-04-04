//
// Created by FanFan on 2025/4/5.
//

#ifndef FLYINGOBJECTINFO_HPP
#define FLYINGOBJECTINFO_HPP
enum class FlyingObjectType {
    Null,
    FireBall
};
enum class FlyingObjectState {
    Start,
    Collide
};
enum class FlyingObjectCollidedState {
    Null,
    Enemy,
    FlyingObject
};
struct FlyingObjectBox {
    std::unordered_map<FlyingObjectState, glm::vec2> size;
    std::unordered_map<FlyingObjectState, std::vector<glm::vec2>> offset;
};
#endif //FLYINGOBJECTINFO_HPP
