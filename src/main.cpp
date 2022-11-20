#include "Builder/GameObjectBuilder.hpp"
#include "Game/Game.hpp"
#include <iostream>

const int VIEW_HEIGHT = 500;
const int VIEW_WIDTH = 500;

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    engine.Init(VIEW_WIDTH, VIEW_HEIGHT, "Mario Game - Platformer Engine", spic::Color::Green());
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_Jump", "./resources/Sprites/Mario/Walk.png");
    GameObjectBuilder gameObjectBuilder {"speler"};
    auto animatedSprite = std::make_shared<platformer_engine::AnimatedSprite>("mario_Jump", 1, 1, 24, 24, 3, 100, 1,
                                                                      platformer_engine::FLIP_NONE,
                                                                      Color::Transparent());
    gameObjectBuilder.AddAnimator(animatedSprite);
    auto gameObject = gameObjectBuilder.GetGameObject();
    auto transform = Transform();
    transform.position = Point();
    transform.rotation = 0;
    transform.position.x = 100;
    transform.position.y = 100;
    gameObject->SetTransform(transform);
    engine.Start();
    
    return 0;
}
