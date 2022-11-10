#include <iostream>
#include "Game/Game.h"

const int VIEW_HEIGHT = 500;
const int VIEW_WIDTH = 500;

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
  PlatformerGame::Game(VIEW_HEIGHT, VIEW_WIDTH);
  return 0;
}
