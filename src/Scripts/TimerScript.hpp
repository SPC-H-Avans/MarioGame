
#ifndef PLATFORMER_GAME_TIMERSCRIPT_HPP
#define PLATFORMER_GAME_TIMERSCRIPT_HPP

#include "BehaviourScript.hpp"
#include "functional"

namespace PlatformerGame {

    class TimerScript : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<BehaviourScript, TimerScript>(*this);
            boost::serialization::void_cast_register<TimerScript, BehaviourScript>();
        }

        TimerScript(int milliseconds, std::function<void()> action);

        void OnStart() override;
    private:
        int _sleepMilliSeconds;
        std::function<void()> _action;
    };
} //namespace PlatformerGame


#endif //PLATFORMER_GAME_TIMERSCRIPT_HPP
