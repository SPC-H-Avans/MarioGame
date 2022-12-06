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

       platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("level2");
      engine.AddScene(builder.GetScene());
        engine.SetActiveScene("level2");
      auto scene =  engine.GetActiveScene();

     //   Scene::ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Map1());
        Scene::ImportLevel("map1","./resources/levels/mario/", "map2.tmx", TileConfig::Map1());
       // Scene::ImportLevel("map1","./resources/levels/mario/", "w1-1.tmx", TileConfig::World1());
//
//        GameObject::Destroy(GameObject::Find(mario.GetName()));

       NetworkingServer networkingServer;
        networkingServer.CreateServer(scene.GetSceneName(), 10, 7779);

      // NetworkingClient networkingClient;
    //    networkingClient.ConnectToServer("192.168.68.120", 7779);


        engine.Start();
        std::cout<<1;
    }
}  // namespace PlatformerGame