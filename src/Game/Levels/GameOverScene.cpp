
#include "GameOverScene.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Engine/Engine.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Color.hpp"
#include "Scripts/TimerScript.hpp"

void GameOverScene::AddToEngine(std::string sceneName, int viewWidth, int viewHeight) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    Scene scene = builder.GetScene();
    Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                           static_cast<double>(viewHeight)};

    auto fontPath = "./resources/fonts/DefaultFont.ttf";
    Transform textPos {{175, 50}, 0, 1.0};
    scene.AddUIObject(std::make_shared<Text>(GameObjectDirector::CreateText(textPos, "gameOverText", "Game Over", fontPath,  100, 50, 48, Color::White())));

    Transform buttonPos {{175, 75}, 0, 1.0};
    std::function<void()> backToMain;
    int w = 15;
    int h = 17;
    Sprite sprite {"mario_walk", w, h };

    GameObjectBuilder objectBuilder("timerObject");
    auto timerObj = objectBuilder.GetGameObject();
    timerObj->AddComponent<BehaviourScript>(std::make_unique<PlatformerGame::TimerScript>(PlatformerGame::TimerScript(3000, []() {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.QueueActiveScene(engine.GetDefaultSceneName());
    })));

    scene.AddObject(*timerObj);

    scene.AddCamera(camera);
    engine.AddScene(scene);
};