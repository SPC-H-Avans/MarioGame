
#ifndef PLATFORMER_GAME_TIMERSCRIPT_HPP
#define PLATFORMER_GAME_TIMERSCRIPT_HPP


#include "BehaviourScript.hpp"
#include "functional"

namespace PlatformerGame {

    class TimerScript : public spic::BehaviourScript {
    public:
        TimerScript(int milliseconds, std::function<void()> action);

        void OnStart() override;

        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
        }
    private:
        int _sleepMilliSeconds;
        std::function<void()> _action;
    };
} //namespace PlatformerGame


#endif //PLATFORMER_GAME_TIMERSCRIPT_HPP
