#include "Game.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Networking/NetworkingServer.hpp"
#include "Levels/MainMenu.hpp"
#include "Levels/Level1.hpp"
#include "Game/Levels/Level2.hpp"
#include "Game/Levels/GameOverScene.hpp"
#include "UI/FPSCounter.hpp"

constexpr bool FULLSCREEN = false;
constexpr bool LOGGING = true;
constexpr int DEFAULT_FONT_SIZE = 50;
const Color DEFAULT_FONT_COLOUR = Color::Yellow();

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan(), FULLSCREEN, LOGGING);

        auto level1 = engine.GetDataManager().LoadData<Scene>("level1");
        if(level1.has_value()) {
            Debug::Log("A level has been found in the saveFile with the name: " + level1->GetSceneName());
        }

        // coin counter
        auto coinCounter = PlatformerGame::CoinCounter(
                Transform{Point{275, 10}, 0, 1.0},
                "coinCounter",
                "COINS: ",
                "./resources/fonts/MarioFont.ttf",
                48, Color::Yellow(),
                160, 50);
        auto coinCounterPtr = std::make_shared<PlatformerGame::CoinCounter>(coinCounter);
        // fps counter
        std::string defaultFont = "./resources/fonts/DefaultFont.ttf";
        auto fpsCounter = platformer_engine::FPSCounter(
                Transform {Point{450, 0}, 0, 1.0},
                defaultFont,
                DEFAULT_FONT_SIZE,
                DEFAULT_FONT_COLOUR,
                DEFAULT_FONT_SIZE / 2, DEFAULT_FONT_SIZE / 2,
                KeyCode::F);
        auto fpsCounterPtr = std::make_shared<platformer_engine::FPSCounter>(fpsCounter);

        MainMenu::AddToEngine("mainmenu", viewWidth, viewHeight, fpsCounterPtr);
        Level1::AddToEngine("level1", viewWidth, viewHeight, coinCounterPtr, fpsCounterPtr);
        Level2::AddToEngine("level2", viewWidth, viewHeight, coinCounterPtr, fpsCounterPtr);
        GameOverScene::AddToEngine("gameover", viewWidth, viewHeight, fpsCounterPtr);

       NetworkingServer networkingServer;
       networkingServer.CreateServer("mainmenu", 10, 7778);

     // NetworkingClient networkingClient;
     // networkingClient.ConnectToServer("192.168.68.107", 7778, viewWidth, viewHeight);


        engine.Start();
        std::cout << 1;
    }
}  // namespace PlatformerGame