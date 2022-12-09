#ifndef PLATFORMER_GAME_COINCOUNTERBEHAVIOUR_HPP
#define PLATFORMER_GAME_COINCOUNTERBEHAVIOUR_HPP

#include "BehaviourScript.hpp"
#include "Color.hpp"

namespace PlatformerGame {
    class CoinCounterBehaviour : public spic::BehaviourScript {
    public:
        CoinCounterBehaviour(std::string textId, std::string text, std::string fontPath, int fontSize, spic::Color fontColor);

        void OnUpdate() override;

    private:
        int _lastCoins = 0;

        const std::string _textId;
        const std::string _text;
        const std::string _fontPath;
        const int _fontSize;
        const spic::Color _fontColor;
    };
}

#endif //PLATFORMER_GAME_COINCOUNTERBEHAVIOUR_HPP
