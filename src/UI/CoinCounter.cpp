#include "CoinCounter.hpp"
#include "Engine/Engine.hpp"
#include "Director/GameObjectDirector.hpp"

PlatformerGame::CoinCounter::CoinCounter(const spic::Transform transform, const std::string textId, const std::string text, const std::string fontPath, const int fontSize,
                                         const spic::Color fontColor, const int width, const int height)
                                         : _textId(textId), _text(text), _fontPath(fontPath), _fontSize(fontSize), _fontColor(fontColor), _coins(0) {
    std::string coinText = _text + std::to_string(_coins);
    GameObjectDirector::CreateText(
            transform,
            _textId,
            coinText,
            _fontPath,
            width, height,
            _fontSize, _fontColor);
    platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(_textId, _fontPath, coinText, _fontSize, _fontColor);
}

void PlatformerGame::CoinCounter::AddCoin() {
    _coins++;
    std::string text = _text + std::to_string(_coins);
    platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(_textId, _fontPath, text, _fontSize, _fontColor);
}

PlatformerGame::CoinCounter::CoinCounter(): _fontColor(Color::Transparent()) {

}

BOOST_CLASS_EXPORT(PlatformerGame::CoinCounter);
