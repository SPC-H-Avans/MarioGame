
#include "FlagBehaviour.hpp"
#include "GameObject.hpp"
#include "Engine/Engine.hpp"
#include "boost/serialization/export.hpp"

namespace PlatformerGame {
    void FlagBehaviour::OnTriggerEnter2D(Collision collision) {
        auto collidingObject = collision.GetSelfCollider()->GetGameObject().lock();

        if(collidingObject->GetTag() == "player") {
            auto &engine = platformer_engine::Engine::GetInstance();
            auto nextScene = engine.GetActiveScene().GetNextScene();
            std::string next;

            if(nextScene.has_value()) {
                next = nextScene.value();
                engine.SetActiveScene(next);
            } else {
                engine.SetActiveScene(engine.GetDefaultSceneName());
            }
        }
    }
}

BOOST_CLASS_EXPORT(PlatformerGame::FlagBehaviour)
