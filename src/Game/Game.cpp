#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "../TileConfig.hpp"

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan());

        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder();
        engine.SetActiveScene(builder.GetScene());
        std::unique_ptr<Scene>& scene =  engine.GetActiveScene();

        engine.GetActiveScene()->ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Level1());
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_Jump", "./resources/Sprites/Mario/Walk.png");
        GameObjectBuilder gameObjectBuilder{"speler"};
        auto sprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump", 1, 1, 24, 24, 3, 100, 1,
                                                                          platformer_engine::FLIP_NONE,
                                                                          Color::Transparent(), 1.0);
        gameObjectBuilder.AddAnimator(sprite);
        auto gameObject = gameObjectBuilder.GetGameObject();
        auto transform = Transform { Point {100, 250}, 0, 1.0 };
        gameObject->SetTransform(transform);
        scene->AddObject(gameObject);

        engine.Start();
        std::cout<<1;
    }
}  // namespace PlatformerGame