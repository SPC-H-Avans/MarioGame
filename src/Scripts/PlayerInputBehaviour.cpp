#include "PlayerInputBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Input.hpp"
#include "Engine/Engine.hpp"
#include "AudioSource.hpp"

const int JUMP_FORCE = -55;

namespace PlatformerGame {

    void PlayerInputBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
        if (player == nullptr ||
            player->GetOwnerId() != platformer_engine::Engine::GetInstance().GetLocalClientId())
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
            if (spic::Input::GetKey(KeyCode::UP_ARROW) || spic::Input::GetKey(KeyCode::SPACE)) {
                if (!playerRigidBody->CanMoveTo(CollisionPoint::Bottom)) {
                    auto audioSource = std::dynamic_pointer_cast<AudioSource>(player->GetComponent<AudioSource>());
                    if (audioSource != nullptr) {
                        audioSource->PlaySound("jump");
                    }
                    point.y += JUMP_FORCE;
                }
            }

            playerRigidBody->AddForce(point);
        }
    }
}  // namespace PlatformerGame
BOOST_CLASS_EXPORT(PlatformerGame::PlayerInputBehaviour);