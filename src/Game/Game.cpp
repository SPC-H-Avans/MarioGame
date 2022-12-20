#include "Game.hpp"
#include "Builder/GameObjectBuilder.hpp"
#include "Builder/SceneBuilder.hpp"
#include "TileConfig.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Networking/NetworkingServer.hpp"
#include "Networking/NetworkingClient.hpp"
#include "Levels/MainMenu.hpp"
#include "Levels/Level1.hpp"
#include "Game/Levels/Level2.hpp"
#include "Game/Levels/GameOverScene.hpp"

constexpr bool FULLSCREEN = false;
constexpr bool LOGGING = true;

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan(), FULLSCREEN, LOGGING);

        MainMenu::AddToEngine("mainmenu", viewWidth, viewHeight);
        Level1::AddToEngine("level1", viewWidth, viewHeight);
        Level2::AddToEngine("level2", viewWidth, viewHeight);
        GameOverScene::AddToEngine("gameover", viewWidth, viewHeight);

       NetworkingServer networkingServer;
       networkingServer.CreateServer("mainmenu", 10, 7778);

     // NetworkingClient networkingClient;
     // networkingClient.ConnectToServer("192.168.68.107", 7778, viewWidth, viewHeight);

        engine.Start();
        std::cout << 1;
    }
}  // namespace PlatformerGame