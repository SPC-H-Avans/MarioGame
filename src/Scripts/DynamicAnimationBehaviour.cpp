#include "DynamicAnimationBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "Animator.hpp"
#include "BoxCollider.hpp"
#include "Engine/Engine.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"

const double VELOCITY_MARGIN = 0.1;

namespace PlatformerGame {

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(platformer_engine::AnimatedSprite idleSprite,
                                                         platformer_engine::AnimatedSprite walkSprite,
                                                         platformer_engine::AnimatedSprite jumpSprite)
            : _idleSprite(idleSprite), _walkSprite(walkSprite), _jumpSprite(jumpSprite)
    { }

    void DynamicAnimationBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
        if(player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId()) return;
        auto playerRigidBody = std::dynamic_pointer_cast<RigidBody>(player->GetComponent<RigidBody>());

        auto velocity = playerRigidBody->GetVelocity();
        if(velocity.x != _lastVelocity.x || velocity.y != _lastVelocity.y) {
            _lastVelocity.x = velocity.x;
            _lastVelocity.y = velocity.y;
            auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
            if (playerRigidBody != nullptr && playerAnimator != nullptr) {
                if (velocity.y != 0) {
                    _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                    playerAnimator->SetActiveAnimation(_jumpSprite.GetSpriteId());
                } else if (velocity.x > VELOCITY_MARGIN || velocity.x < -VELOCITY_MARGIN) {
                    playerAnimator->SetActiveAnimation(_walkSprite.GetSpriteId());
                } else {
                    playerAnimator->SetActiveAnimation(_idleSprite.GetSpriteId());
                }
            }
        }
    }

    DynamicAnimationBehaviour::DynamicAnimationBehaviour()= default;
}  // namespace PlatformerGame

BOOST_CLASS_EXPORT(PlatformerGame::DynamicAnimationBehaviour);