#include "SmallMarioState.hpp"
#include "Engine/Engine.hpp"
#include "Input.hpp"
#include "AudioSource.hpp"
#include "StarMarioState.hpp"
#include "constants/Sprites.hpp"

const double VELOCITY_MARGIN = 0.1;
const int JUMP_FORCE = -65;

namespace PlatformerGame {
    void PlatformerGame::SmallMarioState::Animate(std::shared_ptr<spic::GameObject> player) {
        if(player == nullptr || player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId()) return;
        auto playerRigidBody = std::dynamic_pointer_cast<RigidBody>(player->GetComponent<RigidBody>());

        auto velocity = playerRigidBody->GetVelocity();
        if(velocity.x != _lastVelocity.x || velocity.y != _lastVelocity.y) {
            _lastVelocity.x = velocity.x;
            _lastVelocity.y = velocity.y;
            auto playerAnimator = std::dynamic_pointer_cast<Animator>(player->GetComponent<Animator>());
            if (playerRigidBody != nullptr && playerAnimator != nullptr) {
                if (velocity.y != 0) {
                    if (_lastMoveRight) playerAnimator->SetActiveAnimation(constants::JUMP_SPRITE_ID);
                    else playerAnimator->SetActiveAnimation(constants::JUMP_SPRITE_ID + constants::HORIZONTAL_FLIP_SUFFIX);
                } else if (velocity.x > VELOCITY_MARGIN || velocity.x < -VELOCITY_MARGIN) {
                    if (velocity.x >= 0) {
                        playerAnimator->SetActiveAnimation(constants::WALK_SPRITE_ID);
                        _lastMoveRight = true;
                    }
                    else {
                        playerAnimator->SetActiveAnimation(constants::WALK_SPRITE_ID + constants::HORIZONTAL_FLIP_SUFFIX);
                        _lastMoveRight = false;
                    }
                } else {
                    if (_lastMoveRight) playerAnimator->SetActiveAnimation(constants::IDLE_SPRITE_ID);
                    else playerAnimator->SetActiveAnimation(constants::IDLE_SPRITE_ID + constants::HORIZONTAL_FLIP_SUFFIX);
                }
            }
        }
    }

    void PlatformerGame::SmallMarioState::RegisterInput(std::shared_ptr<spic::GameObject> player, std::unique_ptr<MarioState>& currentState) {
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

            if (spic::Input::GetKeyDown(KeyCode::C)) { // C stands for Cheat
                currentState = std::make_unique<StarMarioState>();
            }
        }
    }

    void PlatformerGame::SmallMarioState::TouchEnemy(Collision collision) {
        auto &engine = platformer_engine::Engine::GetInstance();
        engine.QueueActiveScene("gameover");
    }
}

BOOST_CLASS_EXPORT(PlatformerGame::SmallMarioState);