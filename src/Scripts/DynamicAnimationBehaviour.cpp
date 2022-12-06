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
        auto playerRigidBody = std::dynamic_pointer_cast<PlayerRigidBody>(player->GetComponent<RigidBody>());
        auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
        if (playerRigidBody != nullptr && playerAnimator != nullptr) {
            if (playerRigidBody->GetVelocity().y != 0) {
                _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                playerAnimator->SetActiveAnimation(_jumpSprite.GetSpriteId());
            } else if (playerRigidBody->GetVelocity().x > 0.1 || playerRigidBody->GetVelocity().x < -0.1) {
                playerAnimator->SetActiveAnimation(_walkSprite.GetSpriteId());
            } else {
                playerAnimator->SetActiveAnimation(_idleSprite.GetSpriteId());
            }
        }
    }
}  // namespace PlatformerGame