#ifndef PLATFORMER_GAME_STARMARIOSTATE_HPP
#define PLATFORMER_GAME_STARMARIOSTATE_HPP

#include "MarioState.hpp"

namespace PlatformerGame {
    class StarMarioState : public MarioState {
    public:
        StarMarioState();

        void Animate(std::shared_ptr<spic::GameObject> player) override;

        void RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState>& currentState) override;

        void TakeDamage() override;

    private:
        int _timer;
    };
}

#endif //PLATFORMER_GAME_STARMARIOSTATE_HPP
