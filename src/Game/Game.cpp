#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "TileConfig.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Scripts/PlayerInputBehaviour.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Networking/NetworkingServer.hpp"
#include "Networking/NetworkingClient.hpp"

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan());

        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level1");
        engine.AddScene(builder.GetScene());
        engine.SetActiveScene("level1");
        auto scene =  engine.GetActiveScene();

//        Scene::ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Map1());
//        Scene::ImportLevel("map1","./resources/levels/mario/", "map2.tmx", TileConfig::Map1());
        Scene::ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1());

        GameObjectBuilder gameObjectBuilder{"speler"};
        int w = 15;
        int h = 17;

        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle", "./resources/Sprites/Mario/Idle.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk", "./resources/Sprites/Mario/Walk.png");
        platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump", "./resources/Sprites/Mario/Jump.png");
        auto idleSprite = platformer_engine::AnimatedSprite("mario_idle", w, h, 1);
        auto walkSprite = platformer_engine::AnimatedSprite("mario_walk", w, h, 3);
        auto jumpSprite = platformer_engine::AnimatedSprite("mario_jump", w + 1, h - 1, 1, 1, 1, 100, platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip

        auto transform = Transform { Point {100, 250}, 0, 1.0 };
        auto animations = std::vector<platformer_engine::AnimatedSprite> {idleSprite, walkSprite, jumpSprite};
        auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                std::make_shared<platformer_engine::CollisionBehaviour>(),
                std::make_shared<PlatformerGame::PlayerInputBehaviour>(),
                std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(idleSprite, walkSprite, jumpSprite)
        };

        auto mario = GameObjectDirector::CreatePlayer(0, transform, w, h - 1, animations, behaviourScripts);

        NetworkingServer networkingServer;
        networkingServer.CreateServer(scene.GetSceneName(), 10, 7779);

//        NetworkingClient networkingClient;
//        networkingClient.ConnectToServer("127.0.0.1", 7779);


        engine.Start();
        std::cout<<1;
    }
}  // namespace PlatformerGame