#include "StarBehaviour.hpp"
#include "Engine/Engine.hpp"
#include "MarioBehaviour.hpp"
#include "Scripts/MarioStates/StarMarioState.hpp"

void PlatformerGame::StarBehaviour::OnTriggerEnter2D(Collision collision) {
    auto gameObject = collision.GetOtherCollider()->GetGameObject().lock();
    if(gameObject) {
        if(gameObject->GetTag() != "player") return;

        // put mario in the star state
        auto marioScripts = gameObject->GetComponents<BehaviourScript>();
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
    } else {
        gameObject.reset();
    }

}

BOOST_CLASS_EXPORT(PlatformerGame::StarBehaviour);
