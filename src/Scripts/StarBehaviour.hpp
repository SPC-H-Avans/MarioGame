#ifndef PLATFORMER_GAME_STARBEHAVIOUR_HPP
#define PLATFORMER_GAME_STARBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace PlatformerGame {
    class StarBehaviour : public spic::BehaviourScript {

        void OnTriggerEnter2D(Collision collision) override;
    };
}

#endif //PLATFORMER_GAME_STARBEHAVIOUR_HPP
