
#include "MarioBehaviour.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"

namespace PlatformerGame {

    void MarioBehaviour::OnUpdate() {
        auto object = this->GetGameObject().lock();
        if(object != nullptr) {
            if(object->GetTransform().position.y > 330) { //330 is void in this case
                auto &engine = platformer_engine::Engine::GetInstance();
                engine.SetActiveScene("gameover");
            }
        }
    }

    void MarioBehaviour::OnTriggerEnter2D(Collision collision) {
        auto collidingObject = collision.GetCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "enemy") { //Might expand this in future
            auto &engine = platformer_engine::Engine::GetInstance();
            engine.SetActiveScene("gameover");
        }
    }
}