#include "SmallMarioState.hpp"
#include "Engine/Engine.hpp"
#include "Physics/PlayerRigidBody.hpp"

const double VELOCITY_MARGIN = 0.1;

namespace PlatformerGame {
    SmallMarioState::SmallMarioState() {
    }

    void PlatformerGame::SmallMarioState::Animate(std::shared_ptr<spic::GameObject> player) {
        if(player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId()) return;
        auto playerRigidBody = std::dynamic_pointer_cast<PlayerRigidBody>(player->GetComponent<RigidBody>());

        auto velocity = playerRigidBody->GetVelocity();
        if(velocity.x != _lastVelocity.x || velocity.y != _lastVelocity.y) {
            _lastVelocity.x = velocity.x;
            _lastVelocity.y = velocity.y;
            auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
            if (playerRigidBody != nullptr && playerAnimator != nullptr) {
                if (velocity.y != 0) {
//                    _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                    playerAnimator->SetActiveAnimation("mario_jump");
                } else if (velocity.x > VELOCITY_MARGIN || velocity.x < -VELOCITY_MARGIN) {
                    playerAnimator->SetActiveAnimation("mario_walk");
                } else {
                    playerAnimator->SetActiveAnimation("mario_idle");
                }
            }
        }
    }

    void PlatformerGame::SmallMarioState::RegisterInput() {

    }

    void PlatformerGame::SmallMarioState::TakeDamage() {

    }
}