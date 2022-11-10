#include "Game.h"

namespace PlatformerGame {
    Game::Game(int viewHeight, int viewWidth) {
    platformer_engine::Engine::GetInstance().Init(viewHeight, viewWidth, "Mario Game", spic::Color::Green());
    }
} // PlatformerGame