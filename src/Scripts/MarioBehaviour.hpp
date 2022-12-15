
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
        }

        void OnUpdate() override;

        void OnTriggerEnter2D(Collision collision) override;

    private:
        std::unique_ptr<MarioState> _state = std::make_unique<SmallMarioState>();
    };
} //namespace PlatformerGame



#endif //PLATFORMER_GAME_MARIOBEHAVIOUR_HPP
