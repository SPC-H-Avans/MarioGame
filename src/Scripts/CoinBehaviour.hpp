#ifndef PLATFORMER_GAME_COINBEHAVIOUR_HPP
#define PLATFORMER_GAME_COINBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

class CoinBehaviour : public spic::BehaviourScript {
    void OnTriggerEnter2D(Collision collision) override;
};


#endif //PLATFORMER_GAME_COINBEHAVIOUR_HPP
