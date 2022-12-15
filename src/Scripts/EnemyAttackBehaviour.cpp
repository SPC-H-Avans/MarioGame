#include "EnemyAttackBehaviour.hpp"
#include "Physics/ForceDrivenEntity.hpp"
#include "GameObject.hpp"

void EnemyAttackBehaviour::OnUpdate() {

    auto gameObject = GetGameObject().lock();
    if(gameObject) {
        auto forceDrivenEntity = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(gameObject->GetComponent<platformer_engine::ForceDrivenEntity>());
        if(forceDrivenEntity != nullptr) {
            auto following = forceDrivenEntity->GetFollowing().lock();
            if(following) {
                if(following->GetTransform().position.Distance(gameObject->GetTransform().position) < forceDrivenEntity->GetFollowRange()) {
                    forceDrivenEntity->FollowOn();
                } else {
                    forceDrivenEntity->WanderOn();
                }
            } else {
                forceDrivenEntity->WanderOn();
                following.reset();
            }
        }
    } else {
        gameObject.reset();
    }


}
