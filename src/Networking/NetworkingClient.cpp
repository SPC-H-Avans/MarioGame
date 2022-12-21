#include "NetworkingClient.hpp"
#include "Behaviour/CollisionBehaviour.hpp"
#include "Builder/SceneBuilder.hpp"
#include "Engine/Engine.hpp"
#include "TileConfig.hpp"
#include "Scripts/MarioBehaviour.hpp"
#include "Game/Levels/Level.hpp"

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
        auto& engine = platformer_engine::Engine::GetInstance();
        clientManager.CreateScene(data, dataLength);
        clientManager.SetConnectionStatus(platformer_engine::Connected);

        if(engine.GetQueuedScene() == "gameover" || engine.GetQueuedScene() == "mainmenu") {  return; };

        GameObjectBuilder gameObjectBuilder{"speler"};
        Camera camera = Camera{"camera-" + std::to_string(clientId), "camera", spic::Color::Cyan(), static_cast<double>(viewWidth),
                               static_cast<double>(viewHeight)};

        int w = 15;
        int h = 17;

        auto animations = Level::LoadAnimations();

        auto transform = Transform{Point{100, 220}, 0, 1.0};
        auto behaviourScripts = std::vector<std::shared_ptr<spic::BehaviourScript>>{
                std::make_shared<platformer_engine::CollisionBehaviour>(),
                std::make_shared<PlatformerGame::MarioBehaviour>()
        };
        auto mario = GameObjectFactory::CreatePlayer(clientManager.GetLocalPlayerId(), transform, w, h, animations, behaviourScripts);
        clientManager.InitializeMyClient(mario);

        while(engine.GetQueuedScene().has_value()){
        }

        auto &scene = engine.GetActiveScene();
        mario.Active(true);
        scene.AddObject(mario);
        camera.SetTarget(mario);

        scene.AddCamera(camera);
        scene.SetActiveCameraByName(camera.GetName());
    };

    clientManager.RegisterEventHandler(NET_CREATE_SCENE, onConnect);

}