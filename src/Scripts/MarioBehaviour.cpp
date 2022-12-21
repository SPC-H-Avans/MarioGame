
#include "MarioBehaviour.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"

namespace PlatformerGame {

    void MarioBehaviour::OnUpdate(double  /*speedMultiplier*/) {
        auto object = this->GetGameObject().lock();
        if(object != nullptr) {
            _state->RegisterInput(object, _state);
            _state->Animate(object);

            if(object->GetTransform().position.y > 340) { //340 is void in this case
                _state = std::make_unique<SmallMarioState>(); // dying makes mario small
                auto &engine = platformer_engine::Engine::GetInstance();
                engine.QueueActiveScene("gameover");
            }
        }
    }

    void MarioBehaviour::OnTriggerEnter2D(Collision collision) {
        OnTriggerStay2D(collision);
    }

    void MarioBehaviour::OnTriggerStay2D(Collision collision) {
        auto collidingObject = collision.GetOtherCollider()->GetGameObject().lock();
        auto mario = collision.GetSelfCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "enemy") { //Might expand this in future
            _state->TakeDamage();
            if(collision.Contact() == CollisionPoint::Bottom && mario != nullptr) {
                auto body = std::dynamic_pointer_cast<RigidBody>(mario->GetComponent<RigidBody>());
                if(body != nullptr) {
                    body->AddForce({0, -55}, 1.0);
                }
            }
        }

    }
}

BOOST_CLASS_EXPORT(PlatformerGame::MarioBehaviour);