#ifndef PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace PlatformerGame {

    class PlayerInputBehaviour : public spic::BehaviourScript {
    public:
        void OnUpdate() override;
    private:
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_PLAYERINPUTBEHAVIOUR_HPP
