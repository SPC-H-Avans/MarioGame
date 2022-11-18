#include "Game/Game.hpp"
#include <iostream>

const int VIEW_WIDTH = 500;
const int VIEW_HEIGHT = 500;

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    PlatformerGame::Game game {VIEW_WIDTH, VIEW_HEIGHT};

    return 0;
}
