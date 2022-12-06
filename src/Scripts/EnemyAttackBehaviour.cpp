#include "EnemyAttackBehaviour.hpp"
#include "Physics/ForceDrivenEntityBody.hpp"

namespace PlatformerGame {

    void EnemyAttackBehaviour::OnUpdate() {
        auto enemy = GetGameObject().lock();
        auto enemyRigidBody = std::dynamic_pointer_cast<ForceDrivenEntityBody>(enemy->GetComponent<RigidBody>());
        if (enemyRigidBody != nullptr) {
            enemyRigidBody->Update(1);
        }
    }
}  // namespace PlatformerGame