#include "Level1.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"

void Level1::AddToEngine(std::string sceneName, int viewWidth, int viewHeight) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    Scene scene = builder.GetScene();
    scene.ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1(scene));
    scene.SetNextScene("level2");

    platformer_engine::AudioManager::GetInstance().SetVolume(50);

    platformer_engine::AudioManager::GetInstance().LoadMusic("overworld", "./resources/audio/music/smb_overworld_theme.mp3");
    platformer_engine::AudioManager::GetInstance().LoadSound("jump", "./resources/audio/sounds/smb_jump-small.wav");
    platformer_engine::AudioManager::GetInstance().PlayMusic("overworld", true);

    AddPlayer(scene, 100, 175, viewWidth, viewHeight);
    AddFPSCounter(scene, 450, 0);

    engine.AddScene(scene);
};