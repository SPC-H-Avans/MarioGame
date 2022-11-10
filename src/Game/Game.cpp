#include "Game.hpp"

namespace PlatformerGame {
    Game::Game(int viewHeight, int viewWidth) {
    platformer_engine::Engine::GetInstance().Init(viewWidth, viewHeight, "Mario Game", spic::Color::Green());
    }
} // PlatformerGame