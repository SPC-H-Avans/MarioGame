#include "Builder/GameObjectBuilder.hpp"
#include "Game/Game.hpp"
#include <iostream>

const int VIEW_WIDTH = 480;
const int VIEW_HEIGHT = 270;

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    PlatformerGame::Game game {VIEW_WIDTH, VIEW_HEIGHT};

    return 0;
}
