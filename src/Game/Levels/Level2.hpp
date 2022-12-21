#ifndef PLATFORMER_GAME_LEVEL2_HPP
#define PLATFORMER_GAME_LEVEL2_HPP

#include "Scene.hpp"
#include "Level.hpp"
#include "UI/CoinCounter.hpp"
#include "UI/FPSCounter.hpp"

class Level2 : Level {
public:
    static void AddToEngine(std::string sceneName, int viewWidth, int viewHeight,
                            const std::shared_ptr<PlatformerGame::CoinCounter>& coinCounter,
                            const std::shared_ptr<platformer_engine::FPSCounter>& fpsCounter);
};

#endif //PLATFORMER_GAME_LEVEL2_HPP
