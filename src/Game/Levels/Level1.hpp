#ifndef PLATFORMER_GAME_LEVEL1_HPP
#define PLATFORMER_GAME_LEVEL1_HPP

#include "Scene.hpp"
#include "Level.hpp"

class Level1 : Level {
public:
    static void AddToEngine(std::string sceneName, int viewWidth, int viewHeight);
};

#endif //PLATFORMER_GAME_LEVEL1_HPP
