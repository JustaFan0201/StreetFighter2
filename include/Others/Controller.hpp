#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <iostream>
#include <ostream>

#include "Util/Input.hpp"
#include "Others/FighterInfo.hpp"
#include <unordered_map>
#include <random>

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
        PlayerType Player;
        std::unordered_map<Keys, Keycode> keyMap;
        float time=0;
        int AiMove=0;

        void InitializeKeyMap() {
            if (Player == PlayerType::Player1) {
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
            else if (Player == PlayerType::Player2) {
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
        explicit Controller(PlayerType playerNum) : Player(playerNum) {
            InitializeKeyMap();
        }
        void Update() {
            if (Player == PlayerType::Ai) {
                time+=Time::GetDeltaTimeMs();
                if (time>1000) {randomBool();}
            }
        }
        void randomBool() {
            time=0;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 4);
            AiMove= dis(gen);
        }
        void SetPlayerController(PlayerType playerNum) {
            Player = playerNum;
            InitializeKeyMap();
        }
        Keycode GetKey(Keys keyNow) {
            return keyMap[keyNow];
        }
        bool IsForward(int direction) {
            if (Player == PlayerType::Ai&&AiMove==0){return true;}
            if(direction==static_cast<int>(FighterDirection::Left)) {
                return Input::IsKeyPressed(keyMap[Keys::RIGHT]);
            }
            if(direction==static_cast<int>(FighterDirection::Right)) {
                return Input::IsKeyPressed(keyMap[Keys::LEFT]);
            }
            return false;
        }
        bool IsBackward(int direction) {
            if (Player == PlayerType::Ai&&AiMove==1){return true;}
            if(direction==static_cast<int>(FighterDirection::Right)) {
                return Input::IsKeyPressed(keyMap[Keys::RIGHT]);
            }
            if(direction==static_cast<int>(FighterDirection::Left)) {
                return Input::IsKeyPressed(keyMap[Keys::LEFT]);
            }
            return false;
        }
        bool IsKeyPressed(Keys keyNow) {
            if (Player == PlayerType::Ai&&AiMove==2){return true;}
            return Input::IsKeyPressed(keyMap[keyNow]);
        }
        bool IsKeyDown(Keys keyNow) {
            if (Player == PlayerType::Ai&&AiMove==3){return true;}
            return Input::IsKeyDown(keyMap[keyNow]);
        }
        bool IsKeyUp(Keys keyNow) {
            if (Player == PlayerType::Ai&&AiMove==4){return true;}
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