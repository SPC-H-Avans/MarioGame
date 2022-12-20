#ifndef PLATFORMER_GAME_LEVEL2_HPP
#define PLATFORMER_GAME_LEVEL2_HPP

#include "Scene.hpp"
#include "Level.hpp"

class Level2 : Level {
public:
    static void AddToEngine(std::string sceneName, int viewWidth, int viewHeight);
};

#endif //PLATFORMER_GAME_LEVEL2_HPP
