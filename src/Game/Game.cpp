#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Director/GameObjectDirector.hpp"

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan());

        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder();
        engine.SetActiveScene(builder.GetScene());
        std::unique_ptr<Scene>& scene =  engine.GetActiveScene();

        //
        platformer_engine::TextureManager::GetInstance().LoadTexture("goomba", "./resources/Sprites/Goomba/Idle.png");
        auto sprite4 = std::make_shared<spic::Sprite>("goomba", 1, 1, 24, 24,
                                                     platformer_engine::FLIP_NONE,
                                                     Color::Transparent(), 1.0);
        platformer_engine::TextureManager::GetInstance().LoadTexture("floor1", "./resources/levels/mario/Tilesets/Tiles/floor1.png");
        auto sprite1 = std::make_shared<spic::Sprite>("floor1", 1, 1, 16, 16,
                                                      platformer_engine::FLIP_NONE,
                                                      Color::Transparent(), 1.0);

        std::map<int, std::function<std::shared_ptr<GameObject>(Transform)>> config { // TODO: find a better place to put this
                {4, [&sprite4](Transform transform){ return GameObjectDirector::CreateTile(sprite4, transform);}}, // 4 is breakable block
                {1, [&sprite1](Transform transform){ return GameObjectDirector::CreateTile(sprite1, transform);}}, // 4 is breakable block
        };
        //

        engine.GetActiveScene()->ImportLevel("map1","./resources/levels/mario/", "map1.tmx", config);
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
    }
}  // namespace PlatformerGame