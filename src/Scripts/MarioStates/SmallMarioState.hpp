#ifndef PLATFORMER_GAME_SMALLMARIOSTATE_HPP
#define PLATFORMER_GAME_SMALLMARIOSTATE_HPP

#include "MarioState.hpp"

namespace PlatformerGame {
    class SmallMarioState : public MarioState {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<MarioState, SmallMarioState>(*this);
            boost::serialization::void_cast_register<SmallMarioState, MarioState>();
        }

        void Animate(std::shared_ptr<spic::GameObject> player) override;

        void RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState>& currentState) override;

        void TouchEnemy(std::shared_ptr<spic::GameObject> player, Collision collision) override;
    };
}

#endif //PLATFORMER_GAME_SMALLMARIOSTATE_HPP
