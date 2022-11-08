//
// Created by Jaap Rodenburg on 07/11/2022.
//

#include "Game.h"

namespace PlatformerGame {
    Game::Game(int viewHeight, int viewWidth) {
    PlatformerEngine::Engine::getInstance().Init(viewHeight, viewWidth, "Mario Game", spic::Color::green());
    }

    bool Game::IsRunning() {
       return PlatformerEngine::Engine::getInstance().isRunning;
    }
} // PlatformerGame