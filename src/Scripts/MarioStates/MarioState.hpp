#ifndef PLATFORMER_GAME_MARIOSTATE_HPP
#define PLATFORMER_GAME_MARIOSTATE_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "Texture/AnimatedSprite.hpp"
#include "Point.hpp"

namespace PlatformerGame {
    class MarioState {
    public:
      template<typename archive>
      void serialize(archive &ar, const unsigned /*version*/) {
        ar & _lastVelocity;
        ar & _lastMoveRight;
      }
        virtual void Animate(std::shared_ptr<spic::GameObject> player) = 0;

        virtual void
        RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState> &currentState) = 0;

        virtual void TakeDamage() = 0;

        virtual ~MarioState() = default;

    protected:
        spic::Point _lastVelocity; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
        bool _lastMoveRight = true; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
    };
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(PlatformerGame::MarioState);

#endif //PLATFORMER_GAME_MARIOSTATE_HPP
