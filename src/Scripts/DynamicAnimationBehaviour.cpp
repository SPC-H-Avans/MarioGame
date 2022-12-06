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
        auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
        if (playerRigidBody != nullptr && playerAnimator != nullptr) {
            if (playerRigidBody->GetYVelocity() != 0) {
                _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                playerAnimator->SetActiveAnimation(_jumpSprite.GetSpriteId());
            } else if (playerRigidBody->GetXVelocity() > 0.1 || playerRigidBody->GetXVelocity() < -0.1) {
                playerAnimator->SetActiveAnimation(_walkSprite.GetSpriteId());
            } else {
                playerAnimator->SetActiveAnimation(_idleSprite.GetSpriteId());
            }
        }
    }

    DynamicAnimationBehaviour::DynamicAnimationBehaviour(): _jumpSprite(_nullSprite),
                                                            _walkSprite(_nullSprite),
                                                            _idleSprite(_nullSprite){

    }
}  // namespace PlatformerGame

BOOST_CLASS_EXPORT(PlatformerGame::DynamicAnimationBehaviour);