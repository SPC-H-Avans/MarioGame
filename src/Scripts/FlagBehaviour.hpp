#ifndef PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace PlatformerGame {

    class FlagBehaviour : public spic::BehaviourScript {
    public:
        void OnTriggerEnter2D(Collision collision) override;
    private:
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
