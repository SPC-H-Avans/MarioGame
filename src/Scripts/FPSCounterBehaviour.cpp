#include "FPSCounterBehaviour.hpp"
#include "Texture/TextureManager.hpp"
#include "Engine/Engine.hpp"
#include "Color.hpp"


PlatformerGame::FPSCounterBehaviour::FPSCounterBehaviour(const std::string textId, const std::string fontPath, const int fontSize, const Color fontColor)
                                                            : _textId(textId), _fontPath(fontPath), _fontSize(fontSize), _fontColor(fontColor)
{ }

void PlatformerGame::FPSCounterBehaviour::OnUpdate() {
    auto fps = platformer_engine::Engine::GetInstance().GetFPS();

    if (fps != _lastFPS) {
        _lastFPS = fps;
        std::string fpsText = std::to_string(fps);
        platformer_engine::TextureManager::GetInstance().CreateOrUpdateUIText(_textId, _fontPath, fpsText, _fontSize, _fontColor);
    }
}
