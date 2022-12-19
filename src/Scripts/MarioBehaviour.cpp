
#include "MarioBehaviour.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"

namespace PlatformerGame {

    void MarioBehaviour::OnUpdate() {
        auto object = this->GetGameObject().lock();
        if(object != nullptr) {
            if(object->GetTransform().position.y > 320) { //320 is void in this case
                auto &engine = platformer_engine::Engine::GetInstance();
                engine.QueueActiveScene("gameover");
            }
        }
    }

    void MarioBehaviour::OnTriggerEnter2D(Collision collision) {
        auto collidingObject = collision.GetOtherCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "enemy") { //Might expand this in future
            auto &engine = platformer_engine::Engine::GetInstance();
            engine.QueueActiveScene("gameover");
        }
    }
}