#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "Orders/OrderType.h"
#include "Protocol/Protocol.h"

#include "ServerGameLobby.h"
#include "ServerInGame.h"
#include "ServerLobby.h"

class Server {
    Protocol protocol;
    ServerInGame inGameServer;
    ServerGameLobby gameLobbyServer;
    ServerLobby serverLobby;

    std::map<OrderType, std::function<void(std::unique_ptr<Order>&)>> orderTranslator;

    void setupLobbyOrders();
    void setupGameLobbyOrders();
    void setupInGameOrders();

public:
    explicit Server(const std::string& port);
    void run();

    // TODO ARREGLAR
    // void shutdown() const;
    //~Server();
};
