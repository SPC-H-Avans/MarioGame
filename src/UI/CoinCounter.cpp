#include "CoinCounter.hpp"
#include "Engine/Engine.hpp"
#include "Director/GameObjectDirector.hpp"
#include "../Scripts/CoinCounterBehaviour.hpp"

PlatformerGame::CoinCounter::CoinCounter(const spic::Transform transform, const std::string fontPath, const int fontSize,
                                         const spic::Color fontColor, const int width, const int height) {
    std::string textId = "COINS: x" + std::to_string(platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectCount());
    std::string text = "0";

    auto obj = GameObjectDirector::CreateText(
            transform,
            textId,
            text,
            fontPath,
            width, height,
            fontSize, fontColor);
    obj.AddComponent<BehaviourScript>(std::make_shared<PlatformerGame::CoinCounterBehaviour>(textId, text, fontPath, fontSize, fontColor));
}
