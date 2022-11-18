#include "Game.hpp"
#include "Builder/SceneBuilder.hpp"

namespace PlatformerGame {
    Game::Game(int viewWidth, int viewHeight) {
        platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        engine.Init(viewWidth, viewHeight, "Mario Game", spic::Color::Cyan());

        platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder();
        engine.SetActiveScene(builder.GetScene());

        engine.GetActiveScene()->ImportLevel("map1","./resources/levels/mario/", "map1.tmx");

        engine.Start();
    }
} // PlatformerGame