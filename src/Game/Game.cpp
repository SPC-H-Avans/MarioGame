#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "TileConfig.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Scripts/PlayerInputBehaviour.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Networking/NetworkingServer.hpp"
#include "Networking/NetworkingClient.hpp"

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

        engine.Start();
        std::cout << 1;
    }
}  // namespace PlatformerGame