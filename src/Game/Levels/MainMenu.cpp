
#include "MainMenu.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Scripts/PlayerInputBehaviour.hpp"
#include "TileConfig.hpp"
#include "UI/FPSCounter.hpp"
#include "AudioSource.hpp"
#include "Scripts/MarioBehaviour.hpp"

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
    auto fontPath = "./resources/fonts/DefaultFont.ttf";
    auto fontSize = 52;
    auto color = Color::Black();
    auto uiText = GameObjectDirector::CreateText(
            Transform{Point{190, 10}, 0, 1.0},
            textId,
            text,
            fontPath,
            100, 60,
            fontSize, color);

    platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(textId, fontPath, text, fontSize, color);

    // test Button
    const auto textureName = "MainMenu_StartBtn";
    const auto spriteSize = 16;
    const auto spriteScale = 4;

    auto buttonSprite = spic::Sprite(textureName, spriteSize, spriteSize);
    buttonSprite.SetSpriteScale(spriteScale);
    auto button = GameObjectDirector::CreateButton(
            Transform{Point{220, 125}, 0, spriteScale},
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