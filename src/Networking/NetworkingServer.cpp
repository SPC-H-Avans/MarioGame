#include "NetworkingServer.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Director/GameObjectDirector.hpp"
#include "Engine/Engine.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Scripts/PlayerInputBehaviour.hpp"
#include "TileConfig.hpp"
#include "UI/FPSCounter.hpp"

void
PlatformerGame::NetworkingServer::CreateServer(const std::string &sceneName, int playerLimit, int port, int viewWidth,
                                               int viewHeight) {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();

    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder(sceneName);
    engine.AddScene(builder.GetScene());
    engine.SetActiveScene(sceneName);
    auto &scene = engine.GetActiveScene();

    //Scene::ImportLevel("map1","./resources/levels/mario/", "map1.tmx", TileConfig::Map1());
    //Scene::ImportLevel("map1","./resources/levels/mario/", "map2.tmx", TileConfig::World1());
    Scene::ImportLevel("map1", "./resources/levels/mario/", "w1-1.tmx", TileConfig::World1());
    //

    //Create Player for server
    GameObjectBuilder gameObjectBuilder{"speler"};
    Camera camera = Camera{"camera-0", "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                           static_cast<double>(viewHeight)};
    int w = 15;
    int h = 17;

    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle",
                                                                 "./resources/Sprites/Mario/Idle.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk",
                                                                 "./resources/Sprites/Mario/Walk.png");
    platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump",
                                                                 "./resources/Sprites/Mario/Jump.png");
    auto idleSprite = platformer_engine::AnimatedSprite("mario_idle", w, h, 1);
    auto walkSprite = platformer_engine::AnimatedSprite("mario_walk", w, h, 3);
    auto jumpSprite = platformer_engine::AnimatedSprite("mario_jump", w + 1, h - 1, 1, 1, 1, 100,
                                                        platformer_engine::FLIP_HORIZONTAL); // 16x16 // TODO: fix flip

    auto transform = Transform{Point{100, 250}, 0, 1.0};
    auto animations = std::vector<platformer_engine::AnimatedSprite>{idleSprite, walkSprite, jumpSprite};
    auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<PlatformerGame::PlayerInputBehaviour>(),
            std::make_shared<PlatformerGame::DynamicAnimationBehaviour>(idleSprite, walkSprite, jumpSprite)
    };

    auto mario = GameObjectDirector::CreatePlayer(0, transform, w, h - 1, animations, behaviourScripts);

    camera.SetTarget(mario);
    scene.AddCamera(camera);

    // fps counter
    auto fontPath = "./resources/fonts/DefaultFont.ttf";
    auto color = Color::Yellow();
    auto counter = platformer_engine::FPSCounter(
            Transform {Point{460, 0}, 0, 1.0},
            fontPath,
            48,
            color,
            16, 16);

    engine.HostServer(sceneName, playerLimit, port);
}
