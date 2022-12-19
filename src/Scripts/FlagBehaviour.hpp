#ifndef PLATFORMER_ENGINE_FLAGBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_FLAGBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace PlatformerGame {

    class FlagBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<Component, FlagBehaviour>(*this);
            boost::serialization::void_cast_register<FlagBehaviour, Component>();
        }

        void OnTriggerEnter2D(Collision collision) override;
    private:
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
