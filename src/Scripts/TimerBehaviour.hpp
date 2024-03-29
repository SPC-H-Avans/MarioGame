
#ifndef PLATFORMER_GAME_TIMERBEHAVIOUR_HPP
#define PLATFORMER_GAME_TIMERBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "functional"

namespace PlatformerGame {

    class TimerBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<BehaviourScript, TimerBehaviour>(*this);
            boost::serialization::void_cast_register<TimerBehaviour, BehaviourScript>();
            ar & _sleepMilliSeconds;
        }

        TimerBehaviour();

        TimerBehaviour(int milliseconds, std::function<void()> action);

        void OnStart() override;
    private:
        int _sleepMilliSeconds;
        std::function<void()> _action;
    };
} //namespace PlatformerGame


#endif //PLATFORMER_GAME_TIMERBEHAVIOUR_HPP
