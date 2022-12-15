#ifndef PLATFORMER_GAME_SMALLMARIOSTATE_HPP
#define PLATFORMER_GAME_SMALLMARIOSTATE_HPP

#include "MarioState.hpp"

namespace PlatformerGame {
    class SmallMarioState : public MarioState {
    public:
        SmallMarioState();

        void Animate(std::shared_ptr<spic::GameObject> player) override;

        void RegisterInput() override;

        void TakeDamage() override;
    };
}

#endif //PLATFORMER_GAME_SMALLMARIOSTATE_HPP
