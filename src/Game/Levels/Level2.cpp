#include "Level2.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"

void Level2::AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                         const std::shared_ptr<PlatformerGame::CoinCounter>& coinCounter,
                         const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    Scene scene = builder.GetScene();
    scene.ImportLevel("map2", "./resources/levels/mario/", "w1-2.tmx", TileConfig::World1(coinCounter));
    scene.AddUIObject(coinCounter->GetUIObject());
    scene.AddUIObject(fpsCounter->GetUIObject());

    AddPlayer(scene, 100, 175, viewWidth, viewHeight);

    engine.AddScene(scene);
}
