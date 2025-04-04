#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "Util/Input.hpp"
#include <unordered_map>

namespace Util {
    enum class Keys {
        Null,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        LP,
        MP,
        HP,
        LK,
        MK,
        HK
    };

    class Controller {
    private:
        int PlayerNum;
        std::unordered_map<Keys, Keycode> keyMap;

        // 初始化按键映射
        void InitializeKeyMap() {
            if (PlayerNum == 1) {
                keyMap[Keys::UP] = Keycode::W;
                keyMap[Keys::DOWN] = Keycode::S;
                keyMap[Keys::LEFT] = Keycode::A;
                keyMap[Keys::RIGHT] = Keycode::D;
                keyMap[Keys::LP] = Keycode::T;
                keyMap[Keys::MP] = Keycode::Y;
                keyMap[Keys::HP] = Keycode::U;
                keyMap[Keys::LK] = Keycode::G;
                keyMap[Keys::MK] = Keycode::H;
                keyMap[Keys::HK] = Keycode::J;
            }
            else if (PlayerNum == 2) {
                keyMap[Keys::UP] = Keycode::UP;
                keyMap[Keys::DOWN] = Keycode::DOWN;
                keyMap[Keys::LEFT] = Keycode::LEFT;
                keyMap[Keys::RIGHT] = Keycode::RIGHT;
                keyMap[Keys::LP] = Keycode::KP_7;
                keyMap[Keys::MP] = Keycode::KP_8;
                keyMap[Keys::HP] = Keycode::KP_9;
                keyMap[Keys::LK] = Keycode::KP_4;
                keyMap[Keys::MK] = Keycode::KP_5;
                keyMap[Keys::HK] = Keycode::KP_6;
            }
        }

    public:
        explicit Controller(int playerNum) : PlayerNum(playerNum) {
            InitializeKeyMap();
        }

        void SetPlayerController(int playerNum) {
            PlayerNum = playerNum;
            InitializeKeyMap();
        }
        Keycode GetKey(Keys keyNow) {
            return keyMap[keyNow];
        }
        bool IsForward(int direction) {
            if(direction==static_cast<int>(FighterDirection::Left)) {
                return Input::IsKeyPressed(keyMap[Keys::RIGHT]);
            }
            if(direction==static_cast<int>(FighterDirection::Right)) {
                return Input::IsKeyPressed(keyMap[Keys::LEFT]);
            }
            return false;
        }
        bool IsBackward(int direction) {
            if(direction==static_cast<int>(FighterDirection::Right)) {
                return Input::IsKeyPressed(keyMap[Keys::RIGHT]);
            }
            if(direction==static_cast<int>(FighterDirection::Left)) {
                return Input::IsKeyPressed(keyMap[Keys::LEFT]);
            }
            return false;
        }
        bool IsKeyPressed(Keys keyNow) {
            return Input::IsKeyPressed(keyMap[keyNow]);
        }
        bool IsKeyDown(Keys keyNow) {
            return Input::IsKeyDown(keyMap[keyNow]);
        }
        bool IsKeyUp(Keys keyNow) {
            return Input::IsKeyUp(keyMap[keyNow]);
        }
        Keys GetPunch() {
            if (Input::IsKeyDown(keyMap[Keys::HP])) {return Keys::HP;}
            if (Input::IsKeyDown(keyMap[Keys::MP])) {return Keys::MP;}
            if (Input::IsKeyDown(keyMap[Keys::LP])) {return Keys::LP;}
            return Keys::Null;
        }
    };

}

#endif // CONTROLLER_HPP