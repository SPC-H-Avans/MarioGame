#include "FPSCounter.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "../Scripts/FPSCounterBehaviour.hpp"

PlatformerGame::FPSCounter::FPSCounter(const Transform transform, const std::string fontPath, const int fontSize,
                                       const Color fontColor, const int width, const int height) {
    std::string textId = "fps" + std::to_string(platformer_engine::Engine::GetInstance().GetActiveScene().GetObjectCount());
    std::string text = "0";
    auto object = GameObjectDirector::CreateText(
            transform,
            textId,
            text,
            fontPath,
            width, height,
            fontSize, fontColor);
    object.AddComponent<BehaviourScript>(std::make_shared<PlatformerGame::FPSCounterBehaviour>(textId, fontPath, fontSize, fontColor));
}
