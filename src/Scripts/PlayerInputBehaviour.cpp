#include "PlayerInputBehaviour.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Input.hpp"

namespace PlatformerGame {

    void PlayerInputBehaviour::OnUpdate() {
        auto player = GetGameObject().lock();
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
                if(!playerRigidBody->CanMoveTo(CollisionPoint::Bottom)) {
                    point.y-=55;
                }
            }

            playerRigidBody->AddForce(point);
        }
    }
}  // namespace PlatformerGame