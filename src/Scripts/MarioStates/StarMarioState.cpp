#include "StarMarioState.hpp"
#include "Engine/Engine.hpp"
#include "Input.hpp"
#include "AudioSource.hpp"
#include "SmallMarioState.hpp"

const double VELOCITY_MARGIN = 0.1;
const int JUMP_FORCE = -65;
const int TIMER_TICKS = 5 * 60;

namespace PlatformerGame {

    StarMarioState::StarMarioState() {
        _timer = TIMER_TICKS;
    }

    void StarMarioState::Animate(std::shared_ptr<spic::GameObject> player) {
        if(player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId()) return;
        auto playerRigidBody = std::dynamic_pointer_cast<RigidBody>(player->GetComponent<RigidBody>());

        auto velocity = playerRigidBody->GetVelocity();
        if(velocity.x != _lastVelocity.x || velocity.y != _lastVelocity.y) {
            _lastVelocity.x = velocity.x;
            _lastVelocity.y = velocity.y;
            auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
            if (playerRigidBody != nullptr && playerAnimator != nullptr) {
                if (velocity.y != 0) {
//                    _jumpSprite.SetFlip(platformer_engine::FLIP_VERTICAL);
                    playerAnimator->SetActiveAnimation("mario_jump_star");
                } else if (velocity.x > VELOCITY_MARGIN || velocity.x < -VELOCITY_MARGIN) {
                    playerAnimator->SetActiveAnimation("mario_walk_star");
                } else {
                    playerAnimator->SetActiveAnimation("mario_idle_star");
                }
            }
        }
    }

    void
    StarMarioState::RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState> &currentState) {
        if (player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId())
            return;
        auto playerRigidBody = std::dynamic_pointer_cast<RigidBody>(player->GetComponent<RigidBody>());
        if (playerRigidBody != nullptr) {
            auto point = Point();

            if (spic::Input::GetKey(KeyCode::LEFT_ARROW)) {
                point.x--;
            }
            if (spic::Input::GetKey(KeyCode::RIGHT_ARROW)) {
                point.x++;
            }
            if (spic::Input::GetKeyDown(KeyCode::UP_ARROW) || spic::Input::GetKeyDown(KeyCode::SPACE)) {
                if (!playerRigidBody->CanMoveTo(CollisionPoint::Bottom)) {
                    auto audioSource = std::dynamic_pointer_cast<AudioSource>(player->GetComponent<AudioSource>());
                    if (audioSource != nullptr) {
                        audioSource->PlaySound("jump");
                    }
                    point.y += JUMP_FORCE;
                }
            }

            playerRigidBody->AddForce(point, 1.0);

            // check if timer should run out
            if (--_timer <= 0) {
                currentState = std::make_unique<SmallMarioState>();
            }

            if (spic::Input::GetKeyDown(KeyCode::C)) { // turn Cheat off
                currentState = std::make_unique<SmallMarioState>();
            }
        }
    }

    void StarMarioState::TakeDamage() {
        // TODO: instead of taking damage, kill the enemy
    }
}

BOOST_CLASS_EXPORT(PlatformerGame::StarMarioState);