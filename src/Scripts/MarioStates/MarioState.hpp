#ifndef PLATFORMER_GAME_MARIOSTATE_HPP
#define PLATFORMER_GAME_MARIOSTATE_HPP

#include "Texture/AnimatedSprite.hpp"
#include "Point.hpp"

namespace PlatformerGame {
    class MarioState {
    public:
        virtual void Animate(std::shared_ptr<spic::GameObject> player) = 0;

        virtual void RegisterInput() = 0;

        virtual void TakeDamage() = 0;

    protected:
        platformer_engine::AnimatedSprite _idleSprite;
        platformer_engine::AnimatedSprite _walkSprite;
        platformer_engine::AnimatedSprite _jumpSprite;

        spic::Point _lastVelocity;
    };
}

#endif //PLATFORMER_GAME_MARIOSTATE_HPP
