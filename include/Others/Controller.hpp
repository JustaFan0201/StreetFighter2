#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <iostream>
#include <ostream>

#include "Util/Input.hpp"
#include "Others/FighterInfo.hpp"
#include <unordered_map>
#include <random>
#include <deque>

namespace Util {
    struct InputRecord {
        SpecialMoveDirection move;
        float timestamp;
        std::vector<bool> attacks={false,false,false,false,false,false};
    };
    class Controller {
    private:
        PlayerType Player;
        std::unordered_map<Keys, Keycode> keyMap;
        float timeForAi=0;
        int AiMove=0;

        Keys CurrentAttack=Keys::Null;
        float MoveDelay=500;
        int MaxInput=6;
        std::deque<InputRecord> inputBuffer;
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
            else if (Player == PlayerType::Ai) {
                keyMap[Keys::UP] = Keycode::UNKNOWN;
                keyMap[Keys::DOWN] = Keycode::UNKNOWN;
                keyMap[Keys::LEFT] = Keycode::UNKNOWN;
                keyMap[Keys::RIGHT] = Keycode::UNKNOWN;
                keyMap[Keys::LP] = Keycode::UNKNOWN;
                keyMap[Keys::MP] = Keycode::UNKNOWN;
                keyMap[Keys::HP] = Keycode::UNKNOWN;
                keyMap[Keys::LK] = Keycode::UNKNOWN;
                keyMap[Keys::MK] = Keycode::UNKNOWN;
                keyMap[Keys::HK] = Keycode::UNKNOWN;
            }
        }
    public:
        explicit Controller(PlayerType playerNum) : Player(playerNum) {
            InitializeKeyMap();
        }
        void Update(int direction,float currentTime) {
            if (Player == PlayerType::Ai) {
                timeForAi += Time::GetDeltaTimeMs();
                if (timeForAi > 1000) { randomBool(); }
            }

            InputRecord currentRecord = { GetCurrentMove(direction), currentTime, GetCurrentAttacks() };
            if (inputBuffer.empty() || IsInputRecordDifferent(currentRecord, inputBuffer.front())) {
                PrintInputBuffer();
                inputBuffer.push_front(currentRecord);
                if (static_cast<int>(inputBuffer.size()) > MaxInput) inputBuffer.pop_back();
            }
        }
        static bool IsInputRecordDifferent(const InputRecord& a, const InputRecord& b) {
            if (a.move != b.move) return true;
            for (size_t i = 0; i < a.attacks.size(); i++) {
                if (a.attacks[i] != b.attacks[i]) return true;
            }
            return false;
        }
        SpecialMoveDirection GetCurrentMove(int direction) {
            bool up = IsKeyPressed(Keys::UP);
            bool down = IsKeyPressed(Keys::DOWN);
            bool forward = IsForward(direction);
            bool backward = IsBackward(direction);

            if(forward) {
                if (down) return SpecialMoveDirection::Forward_down;
                if (up) return SpecialMoveDirection::Forward_up;
                return SpecialMoveDirection::Forward;}
            if (backward) {
                if (down) return SpecialMoveDirection::Backward_down;
                if (up) return SpecialMoveDirection::Backward_up;
                return SpecialMoveDirection::Backward;
            }
            if (up) return SpecialMoveDirection::Up;
            if (down) return SpecialMoveDirection::down;
            return SpecialMoveDirection::Null;
        }
        std::vector<bool> GetCurrentAttacks() {
            bool LP = IsKeyDown(Keys::LP);
            bool MP = IsKeyDown(Keys::MP);
            bool HP = IsKeyDown(Keys::HP);
            bool LK = IsKeyDown(Keys::LK);
            bool MK = IsKeyDown(Keys::MK);
            bool HK = IsKeyDown(Keys::HK);
            return std::vector<bool>{LP,MP,HP,LK,MK,HK};
        }
        static bool IsAttackMatched(const std::vector<bool>& attacks, AttackButton button) {
            switch (button) {
                case AttackButton::ANY_PUNCH:
                    return attacks[0] || attacks[1] || attacks[2];
                case AttackButton::ANY_KICK:
                    return attacks[3] || attacks[4] || attacks[5];
                default:
                    return false;
            }
        }
        bool IsSpecialMove(SpecialMoveInput special) {
            int commandIndex = static_cast<int>(special.command.size()) - 1;
            int bufferIndex = static_cast<int>(inputBuffer.size()) - 1;
            float directionFinishTime = -1.0f;

            for (; bufferIndex >= 0; bufferIndex--) {
                auto record = inputBuffer[bufferIndex];
                if (record.move == special.command[commandIndex]) {
                    commandIndex--;
                    if (commandIndex < 0) {
                        directionFinishTime = record.timestamp;
                        break;
                    }
                }
                else if (record.move != SpecialMoveDirection::Null) {
                    commandIndex = static_cast<int>(special.command.size()) - 1;
                }
            }
            if (commandIndex >= 0) return false;
            for (; bufferIndex >= 0; bufferIndex--) {
                auto record = inputBuffer[bufferIndex];
                if (record.timestamp - directionFinishTime > MoveDelay) {
                    break;
                }
                if (IsAttackMatched(record.attacks, special.requiredAttack)) {
                    CurrentAttack=GetPunch(record);
                    inputBuffer.clear();
                    return true;
                }
            }
            return false;
        }
        //debug
        void PrintInputBuffer() const {
            std::cout <<static_cast<int>(Player)<< "Input History: \n";
            for (const auto& input : inputBuffer) {
                std::cout << "Dir: " << static_cast<int>(input.move) << ", Attacks: ";
                for (bool b : input.attacks) {
                    std::cout << (b ? "1" : "0");
                }
                std::cout << "\n";
            }
        }
        void randomBool() {
            timeForAi=0;
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
        static Keys GetPunch(InputRecord record) {
            if(record.attacks[0]){return Keys::LP;}
            if(record.attacks[1]){return Keys::MP;}
            if(record.attacks[2]){return Keys::HP;}
            if(record.attacks[3]){return Keys::LK;}
            if(record.attacks[4]){return Keys::MK;}
            if(record.attacks[5]){return Keys::HK;}
            return Keys::Null;
        }
        Keys GetCurrentAttackKey(){Keys now=CurrentAttack;CurrentAttack=Keys::Null; return now;}
    };

}

#endif // CONTROLLER_HPP