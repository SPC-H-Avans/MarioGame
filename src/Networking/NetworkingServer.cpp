#include "NetworkingServer.hpp"
#include "Engine/Engine.hpp"

void PlatformerGame::NetworkingServer::CreateServer(const std::string &sceneName, int playerLimit, int port) {
    platformer_engine::Engine &engine = platformer_engine::Engine::GetInstance();
    engine.HostServer(sceneName, playerLimit, port);
}
