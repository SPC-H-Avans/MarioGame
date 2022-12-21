
#include "MarioBehaviour.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"

namespace PlatformerGame {

    void MarioBehaviour::OnUpdate(double  /*speedMultiplier*/) {
        auto object = this->GetGameObject().lock();
        if(object != nullptr) {
            _state->RegisterInput(object, _state);
            _state->Animate(object);

            if(object->GetTransform().position.y > 255) { //255 is void in this case
                _state = std::make_unique<SmallMarioState>(); // dying makes mario small
                auto &engine = platformer_engine::Engine::GetInstance();
                engine.QueueActiveScene("gameover");
            }
        }
    }

    void MarioBehaviour::OnTriggerEnter2D(Collision collision) {
        auto collidingObject = collision.GetOtherCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "enemy") { //Might expand this in future
            _state->TakeDamage();
        }
    }
}

BOOST_CLASS_EXPORT(PlatformerGame::MarioBehaviour);