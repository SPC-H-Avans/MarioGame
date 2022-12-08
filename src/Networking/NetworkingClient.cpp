#include "NetworkingClient.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Engine/Engine.hpp"
#include "Scripts/DynamicAnimationBehaviour.hpp"
#include "Scripts/PlayerInputBehaviour.hpp"
#include "TileConfig.hpp"

void PlatformerGame::NetworkingClient::ConnectToServer(const std::string &serverAddress, int port) {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
//    platformer_engine::SceneBuilder builder = platformer_engine::SceneBuilder("dummyMap");
//    engine.AddScene(builder.GetScene());
//    engine.SetActiveScene("dummyMap");
//    auto scene =  engine.GetActiveScene();
//    Scene::ImportLevel("dummyMap","./resources/levels/mario/", "dummyMap.tmx", TileConfig::Map1());
    engine.JoinServer(serverAddress, port);

         auto &clientManager = engine.GetClientNetworkManager();
        std::function<void(int clientId, const uint8_t *data, size_t dataLength)> onConnect = [&clientManager](int clientId,
                                                                                                           const uint8_t *data,
                                                                                                           size_t dataLength) {
        clientManager.CreateScene(data, dataLength);
        GameObjectBuilder gameObjectBuilder{"speler"};
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
        GameObjectDirector::CreatePlayer(clientManager.GetLocalPlayerId(), transform, w, h, animations, behaviourScripts);
        clientManager.InitializeMyClient(*GameObject::Find(std::string(NET_PLAYER_PREFIX) + std::to_string(clientManager.GetLocalPlayerId())));
    };

    clientManager.RegisterEventHandler(NET_CREATE_SCENE, onConnect);

}
