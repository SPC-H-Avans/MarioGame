#ifndef PLATFORMER_GAME_STARBEHAVIOUR_HPP
#define PLATFORMER_GAME_STARBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace PlatformerGame {
    class StarBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<BehaviourScript, StarBehaviour>(*this);
            boost::serialization::void_cast_register<StarBehaviour, BehaviourScript>();
        }

        void OnTriggerEnter2D(Collision collision) override;
    };
}

#endif //PLATFORMER_GAME_STARBEHAVIOUR_HPP
