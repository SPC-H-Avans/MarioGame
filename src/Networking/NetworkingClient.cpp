#include "NetworkingClient.hpp"
#include "Engine/Engine.hpp"

void PlatformerGame::NetworkingClient::ConnectToServer(const std::string &serverAddress, int port) {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    engine.JoinServer(serverAddress, port);

         auto &clientManager = engine.GetClientNetworkManager();
        std::function<void(int clientId, const uint8_t *data, size_t dataLength)> onConnect = [&clientManager](int clientId,
                                                                                                           const uint8_t *data,
                                                                                                           size_t dataLength) {
        clientManager.CreateScene(data, dataLength);
//        Transform transform;
//        Point position;
//        position.x = 300;
//        position.y = 300;
//        transform.position = position;
//        GameObjectBuilder gameobjectBuilder(std::string(NET_PLAYER_PREFIX) + std::to_string(clientManager.GetLocalPlayerId()));
//        Sprite sprite = Sprite("mario", 15, 17);
//        gameobjectBuilder.AddSprite(sprite);
//        gameobjectBuilder.AddTransform(transform);
//        gameobjectBuilder.GetGameObject();
//
//        auto gameObject = GameObject::Find(std::string(NET_PLAYER_PREFIX) + std::to_string(clientManager.GetLocalPlayerId()));
//        if (gameObject == nullptr) return;
//        clientManager.InitializeMyClient(*gameObject);
    };

    clientManager.RegisterEventHandler(NET_CREATE_SCENE, onConnect);

}
