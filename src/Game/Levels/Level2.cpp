#include "Level2.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"

const auto ENEMY_RANGE = 100;

void Level2::AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                         const std::shared_ptr<PlatformerGame::CoinCounter>& coinCounter,
                         const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    Scene scene = builder.GetScene();

    scene.ImportLevel("map2", "./resources/levels/mario/", "w1-2.tmx", TileConfig::World1(coinCounter));

    auto player = AddPlayer(scene, 100, 175, viewWidth, viewHeight);

    for (auto &enemy : scene.GetObjectsByTag("enemy")) {
        auto forceDrivenEntity = std::dynamic_pointer_cast<platformer_engine::ForceDrivenEntity>(enemy->GetComponent<platformer_engine::ForceDrivenEntity>());

        if(forceDrivenEntity != nullptr) {
            auto marioShared = GameObject::Find(player.GetName());
            const double followRange = ENEMY_RANGE;
            forceDrivenEntity->SetFollowing(marioShared, followRange);
        }
    }

    scene.AddUIObject(coinCounter->GetUIObject());
    scene.AddUIObject(fpsCounter->GetUIObject());

    engine.AddScene(scene);
}
