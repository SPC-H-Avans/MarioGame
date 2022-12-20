
#ifndef PLATFORMER_GAME_GAMEOVERSCENE_HPP
#define PLATFORMER_GAME_GAMEOVERSCENE_HPP

#include "Scene.hpp"
#include "UI/FPSCounter.hpp"

class GameOverScene {
public:
    static void AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                            const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter);
};


#endif //PLATFORMER_GAME_GAMEOVERSCENE_HPP
