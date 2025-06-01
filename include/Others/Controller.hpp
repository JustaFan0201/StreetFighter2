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
        ControllerState currentState=ControllerState::Pause;

        float timeForAiMove=0;
        float timeForAiAttack=0;
        float timeForAiSpecial=0;
        float RandomtimeForAiMove=0;
        float RandomtimeForAiAttack=0;
        float RandomtimeForAiSpecial=0;
        int AiSpecialMoves=0;

        AiMove AiMove=AiMove::None;
        AiAttack AiAttack=AiAttack::None;
        SpecialNumer AiSpecial=SpecialNumer::None;

        Keys CurrentAttack=Keys::Null;
        float MoveDelay=250;
        float AtLeastChargeTime=250;
        int MaxInput=30;
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
                keyMap[Keys::ENTER] = Keycode::RETURN;
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
                keyMap[Keys::ENTER] = Keycode::KP_ENTER;
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
                keyMap[Keys::ENTER] = Keycode::UNKNOWN;
            }
        }
    public:
        explicit Controller(PlayerType playerNum) : Player(playerNum) {
            InitializeKeyMap();
        }
        void SetState(ControllerState state){currentState=state;}
        void SetAiSpecials(int number){AiSpecialMoves=number;}
        void ClearAiAttack() {
            if (Player == PlayerType::Ai) {
                AiAttack=AiAttack::None;
            }
        }
        void ClearAiSpecial() {
            if (Player == PlayerType::Ai) {
                AiSpecial=SpecialNumer::None;
            }
        }
        void AiMovement() {
            timeForAiMove += Time::GetDeltaTimeMs();
            timeForAiAttack += Time::GetDeltaTimeMs();
            timeForAiSpecial += Time::GetDeltaTimeMs();
            if (timeForAiMove > RandomtimeForAiMove) {
                RandomtimeForAiMove=static_cast<float>(randomNum(800,1200));
                AiMove= static_cast<enum AiMove>(randomNum(1,7));
                timeForAiMove=0;
            }
            if (timeForAiAttack > RandomtimeForAiAttack) {
                RandomtimeForAiAttack=static_cast<float>(randomNum(700,1500));
                AiAttack= static_cast<enum AiAttack>(randomNum(1,6));
                timeForAiAttack=0;
            }
            if (timeForAiSpecial > RandomtimeForAiSpecial) {
                RandomtimeForAiSpecial=static_cast<float>(randomNum(2500,5000));
                AiSpecial= static_cast<SpecialNumer>(randomNum(0,AiSpecialMoves));
                timeForAiSpecial=0;
            }
        }
        void Update(int direction,float currentTime) {
            if(currentState==ControllerState::Pause){return;}
            if (Player == PlayerType::Ai) {
                AiMovement();
            }
            InputRecord currentRecord = { GetCurrentMove(direction), currentTime, GetCurrentAttacks() };
            if (inputBuffer.empty() || IsInputRecordDifferent(currentRecord, inputBuffer.front())) {
                //debug
                //PrintInputBuffer(inputBuffer);
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
                case AttackButton::ALL_PUNCH:
                    return (attacks[0] && attacks[1])|| (attacks[1] && attacks[2])||(attacks[0] && attacks[2]);
                case AttackButton::ALL_KICK:
                    return (attacks[3] && attacks[4])|| (attacks[4] && attacks[5])||(attacks[3] && attacks[5]);
                default:
                    return false;
            }
        }

        bool IsSpecialMove(SpecialMoveInput special) {
            if(currentState==ControllerState::Pause){return false;}
            if (Player == PlayerType::Ai) {
                if (AiSpecial==special.SpecialNumer){CurrentAttack=GetPunchOrKick(inputBuffer[0],special.requiredAttack); return true;}
                return false;
            }
            if(special.commandtype==CommandType::Null) {
                return Nullskill(special);
            }
            if(special.commandtype==CommandType::Command) {
                return Commandskill(special);
            }
            if(special.commandtype==CommandType::Pressed) {
                return CommandSkillCharge(special,AtLeastChargeTime);
            }
            return false;
        }

        static bool DirectionContain(SpecialMoveDirection input, SpecialMoveDirection required) {
            // 判斷 input 是否包含 required 的方向成分
            if (required == SpecialMoveDirection::Backward) {
                return input == SpecialMoveDirection::Backward || input == SpecialMoveDirection::Backward_down || input == SpecialMoveDirection::Backward_up;
            }
            if (required == SpecialMoveDirection::down) {
                return input == SpecialMoveDirection::down || input == SpecialMoveDirection::Backward_down || input == SpecialMoveDirection::Forward_down;
            }
            if (required == SpecialMoveDirection::Forward) {
                return input == SpecialMoveDirection::Forward || input == SpecialMoveDirection::Forward_down || input == SpecialMoveDirection::Forward_up;
            }
            if (required == SpecialMoveDirection::Up) {
                return input == SpecialMoveDirection::Up || input == SpecialMoveDirection::Backward_up || input == SpecialMoveDirection::Forward_up;
            }
            return false; // Null方向不管
        }

        bool CommandSkillCharge(SpecialMoveInput special, float ChargeTime) {
            if (inputBuffer.empty()) return false;

            int commandIndex = static_cast<int>(special.command.size()) - 1;
            int bufferIndex = static_cast<int>(inputBuffer.size()) - 1;
            int finishchargeindex=static_cast<int>(inputBuffer.size()) - 1;
            int finishDirectionIndex = -1;

            float chargeStartTime = -1.0f;
            float chargeEndTime = -1.0f;
            bool chargeFound = false;
            bool chargeFoundOnce = false;

            for (int i = bufferIndex; i >= 0; --i) {
                SpecialMoveDirection inputDir = inputBuffer[i].move;

                if (DirectionContain(inputDir, special.command[commandIndex])) {
                    if (!chargeFound) {
                        chargeStartTime = inputBuffer[i].timestamp;
                        chargeFound = true;
                        chargeFoundOnce=true;
                        //std::cout<<"Start"<<std::endl;
                        //PrintInputBuffer(std::deque{inputBuffer[i]});
                    }
                }
                else if(chargeFound&&!DirectionContain(inputDir, special.command[commandIndex])) {
                    chargeEndTime = inputBuffer[i].timestamp;
                    finishchargeindex=i;
                    chargeFound = false;
                    //std::cout<<"End"<<std::endl;
                    //PrintInputBuffer(std::deque{inputBuffer[i]});
                }
            }

            if (!chargeFoundOnce) return false;

            float holdDuration = chargeEndTime - chargeStartTime;
            if (holdDuration < ChargeTime) return false; // 蓄力時間不足
            //std::cout<<"ChargeSucess"<<std::endl;
            --commandIndex;
            bool RightCommandOnce = false;
            float directionFinishTime = -1.0f;

            for (int i = finishchargeindex; i >= 0; --i) {
                auto record = inputBuffer[i];
                if (record.move == special.command[commandIndex]) {
                    commandIndex--;
                    if (commandIndex < 0) {
                        directionFinishTime = record.timestamp;
                        finishDirectionIndex = i;
                        commandIndex = static_cast<int>(special.command.size()) - 2;
                        RightCommandOnce=true;
                    }
                }
                else if (record.move != SpecialMoveDirection::Null) {
                    commandIndex = static_cast<int>(special.command.size()) - 2;
                }
            }
            if (!RightCommandOnce) return false;
            //std::cout<<"CommandSucess"<<std::endl;
            for (int i = finishDirectionIndex ; i >= 0; i--) {
                auto record = inputBuffer[i];
                if (record.timestamp - directionFinishTime > MoveDelay) {
                    return false;
                }
                if (IsAttackMatched(record.attacks, special.requiredAttack)) {
                    CurrentAttack = GetPunchOrKick(record, special.requiredAttack);
                    inputBuffer.clear();
                    if(special.chargetime[CurrentAttack]<=holdDuration) {
                        return true;
                    }
                    CurrentAttack=Keys::Null;
                    return false;
                }
            }
            return false;
        }

        bool Commandskill(SpecialMoveInput special) {
            int commandIndex = static_cast<int>(special.command.size()) - 1;
            int bufferIndex = static_cast<int>(inputBuffer.size()) - 1;
            int finishDirectionIndex = -1;
            float directionFinishTime = -1.0f;
            bool RightCommandOnce=false;
            std::deque<InputRecord> TempData;

            for (; bufferIndex >= 0; bufferIndex--) {
                auto record = inputBuffer[bufferIndex];
                if (record.move == special.command[commandIndex]) {
                    commandIndex--;
                    if (commandIndex < 0) {
                        directionFinishTime = record.timestamp;
                        finishDirectionIndex = bufferIndex;
                        commandIndex = static_cast<int>(special.command.size()) - 1;
                        RightCommandOnce=true;
                    }
                }
                else if (record.move != SpecialMoveDirection::Null) {
                    commandIndex = static_cast<int>(special.command.size()) - 1;
                }
            }
            if (!RightCommandOnce) return false;
            for (int i = finishDirectionIndex ; i >= 0; i--) {
                auto record = inputBuffer[i];
                if (record.timestamp - directionFinishTime > MoveDelay) {
                    return false;
                }
                if (IsAttackMatched(record.attacks, special.requiredAttack)) {
                    CurrentAttack = GetPunchOrKick(record, special.requiredAttack);
                    inputBuffer.clear();
                    return true;
                }
            }
            return false;
        }

        bool Nullskill(SpecialMoveInput special) {
            int bufferIndex = static_cast<int>(inputBuffer.size()) - 1;

            for (; bufferIndex >= 0; bufferIndex--) {
                auto record = inputBuffer[bufferIndex];
                if (IsAttackMatched(record.attacks, special.requiredAttack)) {
                    CurrentAttack = GetPunchOrKick(record, special.requiredAttack);
                    inputBuffer.clear();
                    return true;
                }
            }
            return false;
        }
        //debug
        void PrintInputBuffer(const std::deque<InputRecord>& inputBuffer) const {
            std::cout <<static_cast<int>(Player)<< "Input History: \n";
            for (const auto& input : inputBuffer) {
                std::cout << "Dir: " << static_cast<int>(input.move) << ", Attacks: ";
                for (bool b : input.attacks) {
                    std::cout << (b ? "1" : "0");
                }
                std::cout <<" Time:"<<input.timestamp<< "\n";
            }
        }
        int randomNum(int range_lower,int range_higher) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(range_lower, range_higher);
            return dis(gen);
        }
        void SetPlayerController(PlayerType playerNum) {
            Player = playerNum;
            if (playerNum == PlayerType::Ai) {
                RandomtimeForAiMove=static_cast<float>(randomNum(800,1200));
                RandomtimeForAiAttack=static_cast<float>(randomNum(800,1500));
                RandomtimeForAiSpecial=static_cast<float>(randomNum(2500,5000));
            }
            InitializeKeyMap();
        }
        Keycode GetKey(Keys keyNow) {
            return keyMap[keyNow];
        }
        bool IsForward(int direction) {
            if(currentState==ControllerState::Pause){return false;}
            if (Player == PlayerType::Ai) {
                if (AiMove==AiMove::Forward||AiMove==AiMove::JumpForward){return true;}
                return false;
            }
            if(direction==static_cast<int>(FighterDirection::Left)) {
                return Input::IsKeyPressed(keyMap[Keys::RIGHT]);
            }
            if(direction==static_cast<int>(FighterDirection::Right)) {
                return Input::IsKeyPressed(keyMap[Keys::LEFT]);
            }
            return false;
        }
        bool IsBackward(int direction) {
            if(currentState==ControllerState::Pause){return false;}
            if (Player == PlayerType::Ai) {
                if (AiMove==AiMove::Backward||AiMove==AiMove::JumpBackward){return true;}
                return false;
            }
            if(direction==static_cast<int>(FighterDirection::Right)) {
                return Input::IsKeyPressed(keyMap[Keys::RIGHT]);
            }
            if(direction==static_cast<int>(FighterDirection::Left)) {
                return Input::IsKeyPressed(keyMap[Keys::LEFT]);
            }
            return false;
        }
        bool IsKeyPressed(Keys keyNow) {
            if(currentState==ControllerState::Pause){return false;}
            if (Player == PlayerType::Ai) {
                if (AiMove==AiMove::Crouch&&keyNow==Keys::DOWN){return true;}
                return false;
            }
            return Input::IsKeyPressed(keyMap[keyNow]);
        }
        bool IsKeyDown(Keys keyNow) {
            if(currentState==ControllerState::Pause){return false;}
            if (Player == PlayerType::Ai) {
                if ((AiMove==AiMove::JumpUP||AiMove==AiMove::JumpForward||AiMove==AiMove::JumpBackward)&&keyNow==Keys::UP){AiMove=AiMove::None;return true;}
                if(AiAttack==AiAttack::LP&&keyNow==Keys::LP){return true;}
                if(AiAttack==AiAttack::MP&&keyNow==Keys::MP){return true;}
                if(AiAttack==AiAttack::HP&&keyNow==Keys::HP){return true;}
                if(AiAttack==AiAttack::LK&&keyNow==Keys::LK){return true;}
                if(AiAttack==AiAttack::MK&&keyNow==Keys::MK){return true;}
                if(AiAttack==AiAttack::HK&&keyNow==Keys::HK){return true;}
                return false;
            }
            return Input::IsKeyDown(keyMap[keyNow]);
        }
        bool IsKeyUp(Keys keyNow) {
            if(currentState==ControllerState::Pause){return false;}
            return Input::IsKeyUp(keyMap[keyNow]);
        }
        Keys GetPunchOrKick(InputRecord record,AttackButton request) {
            if (Player == PlayerType::Ai) {
                if(request==AttackButton::ALL_PUNCH){
                    return Keys::LP;
                }
                if(request==AttackButton::ANY_PUNCH) {
                    return ButtonList::punch[randomNum(0,2)];
                }
                if(request==AttackButton::ALL_KICK) {
                    return Keys::LK;
                }
                if(request==AttackButton::ANY_KICK) {
                    return ButtonList::kick[randomNum(0,2)];
                }
            }
            if(record.attacks[0]){return Keys::LP;}
            if(record.attacks[1]){return Keys::MP;}
            if(record.attacks[2]){return Keys::HP;}
            if(record.attacks[3]){return Keys::LK;}
            if(record.attacks[4]){return Keys::MK;}
            if(record.attacks[5]){return Keys::HK;}
            return Keys::Null;
        }
        Keys GetCurrentAttackKey(){Keys now=CurrentAttack;CurrentAttack=Keys::Null; return now;}
        static bool IsInDomainKey(Keys key, const std::vector<Keys>& reqType) {
            for (auto button : reqType) {
                if (key == button) return true;
            }
            return false;
        }
    };
}

#endif // CONTROLLER_HPP