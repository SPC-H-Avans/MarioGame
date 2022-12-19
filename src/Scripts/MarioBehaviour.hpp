
#ifndef PLATFORMER_GAME_MARIOBEHAVIOUR_HPP
#define PLATFORMER_GAME_MARIOBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace PlatformerGame {

    class MarioBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<Component, MarioBehaviour>(*this);
            boost::serialization::void_cast_register<MarioBehaviour, Component>();
        }

        void OnUpdate() override;

        void OnTriggerEnter2D(Collision collision) override;

    private:
    };
} //namespace PlatformerGame



#endif //PLATFORMER_GAME_MARIOBEHAVIOUR_HPP
