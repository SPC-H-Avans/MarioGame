#ifndef PLATFORMER_GAME_NETWORKINGCLIENT_H
#define PLATFORMER_GAME_NETWORKINGCLIENT_H
#include <string>
namespace PlatformerGame {
    class NetworkingClient {
    public:
        NetworkingClient() = default;
        ~NetworkingClient() = default;
        void ConnectToServer(const std::string & serverAddress, int port);
    };
}


#endif //PLATFORMER_GAME_NETWORKINGCLIENT_H
