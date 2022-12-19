#include "StarBehaviour.hpp"
#include "Engine/Engine.hpp"
#include "MarioBehaviour.hpp"
#include "Scripts/MarioStates/StarMarioState.hpp"

void PlatformerGame::StarBehaviour::OnTriggerEnter2D(Collision collision) {
    // put mario in the star state
    auto marioScripts = collision.GetCollider()->GetGameObject().lock()->GetComponents<BehaviourScript>();
    for(auto& scriptComponent : marioScripts) {
        auto script = std::dynamic_pointer_cast<PlatformerGame::MarioBehaviour>(scriptComponent);
        if (script != nullptr) {
            script->SetState(std::make_unique<StarMarioState>());
        }
    }

    // after being picked up, remove the star from the scene and destroy it
    auto starObj = GetGameObject().lock();
    platformer_engine::Engine::GetInstance().GetActiveScene().RemoveObject(starObj->GetName());
    starObj->Destroy(starObj);
}

BOOST_CLASS_EXPORT(PlatformerGame::StarBehaviour);
