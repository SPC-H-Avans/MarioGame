#ifndef PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Texture/AnimatedSprite.hpp"

namespace PlatformerGame {

    class DynamicAnimationBehaviour : public spic::BehaviourScript {
    public:
        DynamicAnimationBehaviour(const platformer_engine::AnimatedSprite& idleSprite,
                                  const platformer_engine::AnimatedSprite& walkSprite,
                                  const platformer_engine::AnimatedSprite& jumpSprite);
        void OnUpdate() override;
    private:
        const platformer_engine::AnimatedSprite& _idleSprite;
        const platformer_engine::AnimatedSprite& _walkSprite;
        const platformer_engine::AnimatedSprite& _jumpSprite;
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP