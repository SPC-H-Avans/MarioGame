#ifndef PLATFORMER_GAME_COINCOUNTER_HPP
#define PLATFORMER_GAME_COINCOUNTER_HPP

#include <memory>

#include "GameObject.hpp"

namespace PlatformerGame {
    class CoinCounter {
    public:
        CoinCounter(spic::Transform transform, std::string textId, std::string text, std::string fontPath, int fontSize,
                    spic::Color fontColor, int width, int height);

        void AddCoin();

    private:
        int _coins;
        std::shared_ptr<spic::GameObject> _obj;

        const std::string _textId;
        const std::string _text;
        const std::string _fontPath;
        const int _fontSize;
        const spic::Color _fontColor;
    };
}

#endif //PLATFORMER_GAME_COINCOUNTER_HPP
