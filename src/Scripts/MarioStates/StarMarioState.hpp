#ifndef PLATFORMER_GAME_STARMARIOSTATE_HPP
#define PLATFORMER_GAME_STARMARIOSTATE_HPP

#include "MarioState.hpp"

namespace PlatformerGame {
    class StarMarioState : public MarioState {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<MarioState, StarMarioState>(*this);
            boost::serialization::void_cast_register<StarMarioState, MarioState>();
            ar & _idleSprite;
            ar & _walkSprite;
            ar & _jumpSprite;
            ar & _lastVelocity;
        }

        StarMarioState();

        void Animate(std::shared_ptr<spic::GameObject> player) override;

        void RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState>& currentState) override;

        void TakeDamage() override;

    private:
        int _timer;
    };
}

#endif //PLATFORMER_GAME_STARMARIOSTATE_HPP
