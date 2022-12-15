#include "SmallMarioState.hpp"
#include "Engine/Engine.hpp"
#include "Physics/PlayerRigidBody.hpp"
#include "Input.hpp"
#include "AudioSource.hpp"
#include "StarMarioState.hpp"

const double VELOCITY_MARGIN = 0.1;
const int JUMP_FORCE = 155; // todo back to 55

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

    void PlatformerGame::SmallMarioState::RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState>& currentState) {
        if (player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId())
            return;
        auto playerRigidBody = std::dynamic_pointer_cast<PlayerRigidBody>(player->GetComponent<RigidBody>());
        if (playerRigidBody != nullptr) {
            auto point = Point();

            if (spic::Input::GetKey(KeyCode::LEFT_ARROW)) {
                point.x--;
            }
            if (spic::Input::GetKey(KeyCode::RIGHT_ARROW)) {
                point.x++;
            }
            if (spic::Input::GetKeyDown(KeyCode::UP_ARROW) || spic::Input::GetKeyDown(KeyCode::SPACE)) {
                if (playerRigidBody->CanMoveTo(CollisionPoint::Bottom) != true) {
                    auto audioSource = std::dynamic_pointer_cast<AudioSource>(player->GetComponent<AudioSource>());
                    if (audioSource != nullptr) {
                        audioSource->PlaySound("jump");
                    }
                }
                point.y += JUMP_FORCE;
            }

            playerRigidBody->AddForce(point);

            if (spic::Input::GetKeyDown(KeyCode::C)) { // C stands for Cheat
                currentState = std::make_unique<StarMarioState>();
            }
        }
    }

    void PlatformerGame::SmallMarioState::TakeDamage() {

    }
}