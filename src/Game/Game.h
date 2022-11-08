#ifndef PLATFORMER_GAME_GAME_H
#define PLATFORMER_GAME_GAME_H

#include "Engine/Engine.hpp"

namespace PlatformerGame {

    class Game{
    public:
        Game(int viewHeight, int viewWidth);
        static bool IsRunning();
    private:

    };

} // PlatformerGame

#endif //PLATFORMER_GAME_GAME_H
