#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "../TileConfig.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "../Scripts/PlayerInputBehaviour.hpp"
#include "../Scripts/DynamicAnimationBehaviour.hpp"
#include "../Scripts/FPSCounterBehaviour.hpp"
#include "../UI/FPSCounter.hpp"

const bool FULLSCREEN = true;

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan(), FULLSCREEN);

        Camera camera = Camera{"camera1", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                               static_cast<double>(viewHeight)};


        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level1");
        engine.AddScene(builder.GetScene());
        engine.SetActiveScene("level1");
        Scene &scene = engine.GetActiveScene();

//        Scene::ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Map1());
//        Scene::ImportLevel("map1","./resources/levels/mario/", "map2.tmx", TileConfig::Map1());
        Scene::ImportLevel("map1", "./resources/levels/mario/", "w1-1.tmx", TileConfig::World1());

        GameObjectBuilder gameObjectBuilder{"speler"};
        int w = 15;
        int h = 17;

        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle",
                                                                     "./resources/Sprites/Mario/Idle.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk",
                                                                     "./resources/Sprites/Mario/Walk.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump",
                                                                     "./resources/Sprites/Mario/Jump.png");
        auto idleSprite = platformer_engine::AnimatedSprite("mario_idle", w, h, 1);
        auto walkSprite = platformer_engine::AnimatedSprite("mario_walk", w, h, 3);
        auto jumpSprite = platformer_engine::AnimatedSprite("mario_jump", w + 1, h - 1, 1, 1, 1, 100,
                                                            platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip

        auto animations = std::vector<platformer_engine::AnimatedSprite>{idleSprite, walkSprite, jumpSprite};
        auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                std::make_shared<platformer_engine::CollisionBehaviour>(),
                std::make_shared<PlatformerGame::PlayerInputBehaviour>(),
                std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(idleSprite, walkSprite, jumpSprite)
        };

        auto mario = GameObjectDirector::CreatePlayer(
                Transform{Point{340, 100}, 0, 1.0},
                w, h - 1, animations, behaviourScripts);

        camera.SetTarget(mario);

        scene.AddCamera(camera);

        // test Text
        auto textId = "coins";
        auto text = "COINS: x00";
        auto fontPath = "./resources/fonts/DefaultFont.ttf";
        auto fontSize = 24;
        auto color = Color::Yellow();
        GameObjectDirector::CreateText(
                Transform{Point{300, 0}, 0, 1.0},
                textId,
                text,
                fontPath,
                100, 50,
                fontSize, color);

        // test update text
        text = "COINS: x99";
        platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(textId, fontPath, text, fontSize, color);

        // test Button
        const auto textureName = "startButton";
        const auto spriteSize = 16;
        const auto spriteScale = 4;

        auto buttonSprite = spic::Sprite(textureName, spriteSize, spriteSize);
        buttonSprite.SetSpriteScale(spriteScale);
        GameObjectDirector::CreateButton(
                Transform{Point{50, 50}, 0, spriteScale},
                "button1",
                buttonSprite,
                "./resources/UI/start.png",
                spriteSize * spriteScale, spriteSize * spriteScale,
                []{ std::cout << "click" << std::endl; });

        // fps counter
        FPSCounter counter = FPSCounter(
                Transform {Point{460, 0}, 0, 1.0},
                fontPath,
                48,
                color,
                16, 16);

        engine.Start();
        std::cout << 1;
    }
}  // namespace PlatformerGame