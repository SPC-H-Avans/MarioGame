
#include "MainMenu.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectFactory.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"
#include "UI/FPSCounter.hpp"
#include "AudioSource.hpp"

void MainMenu::AddToEngine(std::string sceneName, int viewWidth, int viewHeight) {
    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    Scene scene = builder.GetScene();
    scene.SetNextScene("level1");

    Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                           static_cast<double>(viewHeight)};

    // test Text
    auto textId = "MainMenu_Title";
    auto text = "Mario Bros Lite";
    auto fontPath = "./resources/fonts/MarioFont.ttf";
    auto fontSize = 80;
    auto color = Color::Black();
    auto uiText = GameObjectFactory::CreateText(
            Transform{Point{40, 20}, 0, 1.0},
            textId,
            text,
            fontPath,
            400, 70,
            fontSize, color);

    platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(textId, fontPath, text, fontSize, color);

    // test Button
    const auto textureName = "MainMenu_StartBtn";
    const auto spriteSize = 16;
    const auto spriteScale = 4;

    auto buttonSprite = spic::Sprite(textureName, spriteSize, spriteSize);
    buttonSprite.SetSpriteScale(spriteScale);
    auto button = GameObjectFactory::CreateButton(
            Transform{Point{200, 125}, 0, spriteScale},
            "button1",
            buttonSprite,
            "./resources/UI/start.png",
            spriteSize * spriteScale, spriteSize * spriteScale,
            []{ platformer_engine::Engine& engine = platformer_engine::Engine::GetInstance();
                engine.QueueActiveScene(engine.GetActiveScene().GetNextScene().value());
            });

    scene.AddUIObject(std::make_shared<Button>(button));
    scene.AddUIObject(std::make_shared<Text>(uiText));

    scene.AddCamera(camera);

    engine.AddScene(scene);
};