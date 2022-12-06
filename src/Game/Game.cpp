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

       //NetworkingServer networkingServer;
     //  networkingServer.CreateServer(scene.GetSceneName(), 10, 7779);

       NetworkingClient networkingClient;
       networkingClient.ConnectToServer("192.168.68.120", 7779);


        engine.Start();
        std::cout<<1;
    }
}  // namespace PlatformerGame