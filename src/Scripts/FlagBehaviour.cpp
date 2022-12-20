
#include "FlagBehaviour.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"
#include "boost/serialization/export.hpp"
#include "MarioBehaviour.hpp"

namespace PlatformerGame {
    void FlagBehaviour::OnTriggerEnter2D(Collision collision) {
        auto collidingObject = collision.GetCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "player") {
            auto marioBehaviour = collidingObject->GetComponent<MarioBehaviour>();
            for (auto &behaviour : collidingObject->GetComponents<BehaviourScript>()) {
                if (std::dynamic_pointer_cast<MarioBehaviour>(behaviour) != nullptr)
                    std::dynamic_pointer_cast<MarioBehaviour>(behaviour)->SetState(std::make_unique<SmallMarioState>());
            }

            auto &engine = platformer_engine::Engine::GetInstance();
            auto nextScene = engine.GetActiveScene().GetNextScene();
            std::string next;

            if(nextScene.has_value()) {
                next = nextScene.value();
                engine.QueueActiveScene(next);
            } else {
                engine.QueueActiveScene(engine.GetDefaultSceneName());
            }
        }
    }
}

BOOST_CLASS_EXPORT(PlatformerGame::FlagBehaviour)
