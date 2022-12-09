#ifndef PLATFORMER_GAME_COINBEHAVIOUR_HPP
#define PLATFORMER_GAME_COINBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "../UI/CoinCounter.hpp"

namespace PlatformerGame {
    class CoinBehaviour : public spic::BehaviourScript {
    public:
        explicit CoinBehaviour(std::shared_ptr<CoinCounter> counter);

        void OnTriggerEnter2D(Collision collision) override;

    private:
        std::shared_ptr<CoinCounter> _counter;
    };
}

#endif //PLATFORMER_GAME_COINBEHAVIOUR_HPP
