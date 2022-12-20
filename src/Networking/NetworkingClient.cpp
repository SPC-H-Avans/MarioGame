#include "NetworkingClient.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"
#include "Scripts/MarioBehaviour.hpp"

void PlatformerGame::NetworkingClient::ConnectToServer(const std::string &serverAddress, int port, int viewWidth, int viewHeight) {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
//    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("dummyMap");
//    engine.AddScene(builder.GetScene());
//    engine.SetActiveScene("dummyMap");
//    auto scene =  engine.GetActiveScene();
//    Scene::ImportLevel("dummyMap","./resources/levels/mario/", "dummyMap.tmx", TileConfig::Map1());
    engine.JoinServer(serverAddress, port);

         auto &clientManager = engine.GetClientNetworkManager();
        std::function<void(int clientId, const uint8_t *data, size_t dataLength)> onConnect = [&clientManager, viewWidth, viewHeight](int clientId,
                                                                                                           const uint8_t *data,
                                                                                                           size_t dataLength) {
            platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
        clientManager.CreateScene(data, dataLength);
        clientManager.SetConnectionStatus(platformer_engine::Connected);

        if(engine.GetQueuedScene() == "gameover") { GameObject::Destroy(GameObject::Find("timerObject")); return; }
        else if(engine.GetQueuedScene() == "mainmenu") { GameObject::Destroy(GameObject::Find("MainMenu_StartBtn")); return; };

        GameObjectBuilder gameObjectBuilder{"speler"};
            Camera camera = Camera{"camera-" + std::to_string(clientId), "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
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


            platformer_engine::TextureManager::GetInstance().LoadTexture("mario_idle_star",
                                                                         "./resources/Sprites/Mario/Star/Idle.png");
            platformer_engine::TextureManager::GetInstance().LoadTexture("mario_walk_star",
                                                                         "./resources/Sprites/Mario/Star/Walk.png");
            platformer_engine::TextureManager::GetInstance().LoadTexture("mario_jump_star",
                                                                         "./resources/Sprites/Mario/Star/Jump.png");
            auto idleStarSprite = platformer_engine::AnimatedSprite("mario_idle_star", w, h, 6);
            auto walkStarSprite = platformer_engine::AnimatedSprite("mario_walk_star", w, h, 6);
            auto jumpStarSprite = platformer_engine::AnimatedSprite("mario_jump_star", w + 1, h - 1, 6);

        auto transform = Transform{Point{100, 220}, 0, 1.0};
        auto animations = std::vector<platformer_engine::AnimatedSprite>{walkSprite, jumpSprite, idleStarSprite, walkStarSprite, jumpStarSprite, idleSprite};
        auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
            std::make_shared<platformer_engine::CollisionBehaviour>(),
            std::make_shared<PlatformerGame::MarioBehaviour>()
        };
        auto mario = GameObjectDirector::CreatePlayer(clientManager.GetLocalPlayerId(), transform, w, h, animations, behaviourScripts);
        clientManager.InitializeMyClient(*GameObject::Find(std::string(NET_PLAYER_PREFIX) + std::to_string(clientManager.GetLocalPlayerId())));

        while(platformer_engine::Engine::GetInstance().GetQueuedScene().has_value()){
        }

        auto &scene = platformer_engine::Engine::GetInstance().GetActiveScene();
        mario.Active(true);
        scene.AddObject(mario);
        camera.SetTarget(mario);

        scene.AddCamera(camera);
        scene.SetActiveCameraByName(camera.GetName());
    };

    clientManager.RegisterEventHandler(NET_CREATE_SCENE, onConnect);

}
