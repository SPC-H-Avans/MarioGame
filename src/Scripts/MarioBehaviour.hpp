
#ifndef PLATFORMER_GAME_MARIOBEHAVIOUR_HPP
#define PLATFORMER_GAME_MARIOBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Scripts/MarioStates/MarioState.hpp"
#include "Scripts/MarioStates/SmallMarioState.hpp"

namespace PlatformerGame {

    class MarioBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<BehaviourScript, MarioBehaviour>(*this);
            boost::serialization::void_cast_register<MarioBehaviour, BehaviourScript>();
            ar & _state;
        }

        void OnUpdate(double speedMultiplier) override;

        void OnTriggerEnter2D(Collision collision) override;
        void OnTriggerStay2D(Collision collision) override;

        void SetState(std::unique_ptr<MarioState> state) { _state = std::move(state); }

    private:
        std::unique_ptr<MarioState> _state = std::make_unique<SmallMarioState>();
    };
} //namespace PlatformerGame



#endif //PLATFORMER_GAME_MARIOBEHAVIOUR_HPP
