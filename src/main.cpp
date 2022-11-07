#include <iostream>
#include "Game/Game.h"

auto main() -> int {
    try{
        PlatformerGame::Game game = PlatformerGame::Game(500,500);
        while (PlatformerGame::Game::IsRunning()){
        std::cout << "Tick";
        }
        return  0;
    } catch (std::exception& e){
        std::cerr << e.what()
    }
}
