#include "DynamicAnimationBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "Animator.hpp"

namespace PlatformerGame {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(platformer_engine::AnimatedSprite& idleSprite,
                                                         platformer_engine::AnimatedSprite& walkSprite,
                                                         platformer_engine::AnimatedSprite& jumpSprite)
            : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
    { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
        auto rigidBody = std::dynamic_pointer_cast<RigidBody>(player->GetComponent<RigidBody>());
        auto animator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
        if (rigidBody != nullptr && animator != nullptr) {
            if (rigidBody->GetVelocity().y != 0) {
                _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                animator->SetActiveAnimation(_jumpSprite.GetSpriteId());
            } else if (rigidBody->GetVelocity().x > 0.1 || rigidBody->GetVelocity().x < -0.1) {
                animator->SetActiveAnimation(_walkSprite.GetSpriteId());
            } else {
                animator->SetActiveAnimation(_idleSprite.GetSpriteId());
            }
        }
    }
}  // namespace PlatformerGame