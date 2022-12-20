
#ifndef PLATFORMER_GAME_MAINMENU_HPP
#define PLATFORMER_GAME_MAINMENU_HPP

#include "Scene.hpp"
#include "UI/FPSCounter.hpp"

class MainMenu {
public:
    static void AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                            const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter);
};


#endif //PLATFORMER_GAME_MAINMENU_HPP
