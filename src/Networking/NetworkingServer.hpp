#ifndef PLATFORMER_GAME_NETWORKINGSERVER_H
#define PLATFORMER_GAME_NETWORKINGSERVER_H
#include <string>
#include "Scene.hpp"

namespace PlatformerGame {
    class NetworkingServer {
        public:
        NetworkingServer() = default;
        ~NetworkingServer() = default;
        void CreateServer(const std::string& sceneName, int playerLimit, int port);
    };
}


#endif //PLATFORMER_GAME_NETWORKINGSERVER_H
