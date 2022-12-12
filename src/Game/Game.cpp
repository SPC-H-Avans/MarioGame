#include "Game.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Networking/NetworkingServer.hpp"

constexpr bool FULLSCREEN = true;
constexpr bool LOGGING = true;

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan(), FULLSCREEN, LOGGING);

       NetworkingServer networkingServer;
       networkingServer.CreateServer("level1", 10, 7778, viewWidth, viewHeight);

     // NetworkingClient networkingClient;
     // networkingClient.ConnectToServer("192.168.68.107", 7778, viewWidth, viewHeight);

        engine.Start();
        std::cout << 1;
    }
}  // namespace PlatformerGame