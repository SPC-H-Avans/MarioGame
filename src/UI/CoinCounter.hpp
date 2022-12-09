#ifndef PLATFORMER_GAME_COINCOUNTER_HPP
#define PLATFORMER_GAME_COINCOUNTER_HPP

#include <memory>

#include "GameObject.hpp"

namespace PlatformerGame {
    class CoinCounter {
    public:
        CoinCounter(spic::Transform transform, std::string fontPath, int fontSize,
                    spic::Color fontColor, int width, int height);

    private:
        std::shared_ptr<spic::GameObject> _obj;
    };
}

#endif //PLATFORMER_GAME_COINCOUNTER_HPP
