#include "CoinCounterBehaviour.hpp"
#include "Texture/TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "Color.hpp"
#include "Input.hpp"

PlatformerGame::CoinCounterBehaviour::CoinCounterBehaviour(const std::string textId, const std::string text, const std::string fontPath, const int fontSize, const Color fontColor)
        : _textId(textId), _text(text), _fontPath(fontPath), _fontSize(fontSize), _fontColor(fontColor)
{ }

void PlatformerGame::CoinCounterBehaviour::OnUpdate() {

    auto coins = 0;

    if (coins != _lastCoins) {
        _lastCoins = coins;
        std::string fpsText = std::to_string(coins);
        platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(_textId, _fontPath, fpsText, _fontSize, _fontColor);
    }
}