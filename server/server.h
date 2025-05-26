#pragma once
#include <map>

#include <functional>
#include <memory>

#include "Protocol/Protocol.h"
#include "Orders/OrderType.h"

#include "ServerLobby.h"
#include "ServerGameLobby.h"
#include "ServerInGame.h"


class Server {
    Protocol protocol;

    ServerLobby serverLobby;
    ServerGameLobby gameLobbyServer;
    ServerInGame inGameServer;

    std::map<OrderType, std::function<void(std::unique_ptr<Order>&)>> orderTranslator;

    void setupLobbyOrders();
    void setupGameLobbyOrders();
    void setupInGameOrders();

public:
    explicit Server(const char* port);
    void run();


    //TODO ARREGLAR
    //void shutdown() const;
    //~Server();
};

