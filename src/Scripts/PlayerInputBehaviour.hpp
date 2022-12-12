#ifndef PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>

namespace PlatformerGame {

    class PlayerInputBehaviour : public spic::BehaviourScript {
    public:
        template<class Archive>
        void serialize(Archive &ar, unsigned int version) {
            ar & boost::serialization::base_object<BehaviourScript, PlayerInputBehaviour>(*this);
            boost::serialization::void_cast_register<PlayerInputBehaviour, BehaviourScript>();
        }
        void OnUpdate(double deltaTime) override;
    private:
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
