#include "DynamicAnimationBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "Animator.hpp"

namespace PlatformerGame {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(const platformer_engine::AnimatedSprite& idleSprite,
                                                         const platformer_engine::AnimatedSprite& walkSprite,
                                                         const platformer_engine::AnimatedSprite& jumpSprite)
            : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
    { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
        auto playerRigidBody = std::dynamic_pointer_cast<PlayerRigidBody>(player->GetComponent<RigidBody>());
        auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
        if (playerRigidBody != nullptr && playerAnimator != nullptr) {
            if (playerRigidBody->GetYVelocity() != 0) {
                playerAnimator->SetActiveAnimation(_jumpSprite.GetSpriteId());
            } else if (playerRigidBody->GetXVelocity() > 0.1 || playerRigidBody->GetXVelocity() < -0.1) {
                playerAnimator->SetActiveAnimation(_walkSprite.GetSpriteId());
            } else {
                playerAnimator->SetActiveAnimation(_idleSprite.GetSpriteId());
            }
        }
    }
}  // namespace PlatformerGame