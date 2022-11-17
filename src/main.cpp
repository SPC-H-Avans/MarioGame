#include "Game/Game.hpp"
#include <iostream>

const int VIEW_HEIGHT = 500;
const int VIEW_WIDTH = 500;

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {

    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    engine.Init(VIEW_WIDTH, VIEW_HEIGHT, "PlatFormer Engine Debug", spic::Color::Green());
    engine.Start();


    return 0;
}
