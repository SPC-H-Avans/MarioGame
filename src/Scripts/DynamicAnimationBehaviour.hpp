#ifndef PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Texture/AnimatedSprite.hpp"

namespace PlatformerGame {

    class DynamicAnimationBehaviour : public spic::BehaviourScript {
    public:
        DynamicAnimationBehaviour(platformer_engine::AnimatedSprite& idleSprite,
                                  platformer_engine::AnimatedSprite& walkSprite,
                                  platformer_engine::AnimatedSprite& jumpSprite);
        void OnUpdate() override;
    private:
        platformer_engine::AnimatedSprite& _idleSprite;
        platformer_engine::AnimatedSprite& _walkSprite;
        platformer_engine::AnimatedSprite& _jumpSprite;
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP