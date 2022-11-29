#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "../TileConfig.hpp"

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan());

        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level1");
        engine.AddScene(builder.GetScene());
        engine.SetActiveScene("level1");
        auto scene =  engine.GetActiveScene();

        Scene::ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Level1());
//        Scene::ImportLevel("map1","./resources/levels/mario/", "map2.tmx", TileConfig::Level1());

        GameObjectBuilder gameObjectBuilder{"speler"};
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle", "./resources/Sprites/Mario/Idle.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk", "./resources/Sprites/Mario/Walk.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump", "./resources/Sprites/Mario/Jump.png");
        int w = 15;
        int h = 17;
        auto idleSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_idle", 1, 1, w, h, 1, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 1.0);
        auto walkSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_walk", 1, 1, w, h, 3, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 1.0);
        auto jumpSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_jump", 1, 1, w + 1, h - 1, 1, 100, 1,
                                                                              platformer_engine::FLIP_NONE,
                                                                              Color::Transparent(), 1.0);

        auto transform = Transform { Point {100, 250}, 0, 1.0 };
        auto mario = GameObjectDirector::CreatePlayer(idleSprite, walkSprite, jumpSprite, transform, w, h);

        engine.Start();
        std::cout<<1;
    }
}  // namespace PlatformerGame