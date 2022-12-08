#include "DynamicAnimationBehaviour.hpp"
#include "Animator.hpp"
#include "BoxCollider.hpp"
#include "Engine/Engine.hpp"
#include "GameObject.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "RigidBody.hpp"

namespace PlatformerGame {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(platformer_engine::AnimatedSprite idleSprite,
                                                         platformer_engine::AnimatedSprite walkSprite,
                                                         platformer_engine::AnimatedSprite jumpSprite)
            : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
    { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
        if(player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId()) return;
        auto playerRigidBody = std::dynamic_pointer_cast<PlayerRigidBody>(player->GetComponent<RigidBody>());

        auto xVelocity = playerRigidBody->GetXVelocity();
        auto yVelocity = playerRigidBody->GetYVelocity();
        if(xVelocity != _lastVelocity.x || yVelocity != _lastVelocity.y) {
            _lastVelocity.x = xVelocity;
            _lastVelocity.y = yVelocity;
            auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
            if (playerRigidBody != nullptr && playerAnimator != nullptr) {
                if (yVelocity != 0) {
                    _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                    playerAnimator->SetActiveAnimation(_jumpSprite.GetSpriteId());
                } else if (xVelocity > 0.1 || xVelocity < -0.1) {
                    playerAnimator->SetActiveAnimation(_walkSprite.GetSpriteId());
                } else {
                    playerAnimator->SetActiveAnimation(_idleSprite.GetSpriteId());
                }
            }
        }
    }

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(){

    }
}  // namespace PlatformerGame

BOOST_CLASS_EXPORT(PlatformerGame::DynamicAnimationBehaviour);