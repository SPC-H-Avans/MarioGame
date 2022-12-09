
#include "FlagBehaviour.hpp"
#include "GameObject.hpp"

namespace PlatformerGame {
    void FlagBehaviour::OnTriggerEnter2D(Collision collision) {
        auto collidingObject = collision.GetCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "player") {
             //GameOver
        }
    }
}
