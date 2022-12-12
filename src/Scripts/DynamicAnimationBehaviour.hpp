#ifndef PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Texture/AnimatedSprite.hpp"

namespace PlatformerGame {

    class DynamicAnimationBehaviour : public spic::BehaviourScript {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar & boost::serialization::base_object<BehaviourScript, DynamicAnimationBehaviour>(*this);
            boost::serialization::void_cast_register<DynamicAnimationBehaviour, BehaviourScript>();
            ar & _idleSprite;
            ar & _walkSprite;
            ar & _jumpSprite;
        }
        DynamicAnimationBehaviour(platformer_engine::AnimatedSprite idleSprite,
                                  platformer_engine::AnimatedSprite walkSprite,
                                  platformer_engine::AnimatedSprite jumpSprite);

        DynamicAnimationBehaviour();

        void OnUpdate(double deltaTime) override;
    private:
        platformer_engine::AnimatedSprite _idleSprite;
        platformer_engine::AnimatedSprite _walkSprite;
        platformer_engine::AnimatedSprite _jumpSprite;

        platformer_engine::AnimatedSprite _nullSprite;

        Point _lastVelocity;
    };

}  // namespace PlatformerGame

#endif //PLATFORMER_ENGINE_DYNAMICANIMATIONBEHAVIOUR_HPP