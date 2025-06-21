#pragma once

#include "server/Requests/Request.h"
#include "server/Orders/ServerLobbyOrder.h"
#include "server/Handlers/LobbyHandler.h"
#include <map>
#include <memory>
#include <string>
#include <functional>

class ServerLobbyProtocol {
    std::map<uint8_t, std::function<ServerLobbyOrder(const Request&)>> requestHandlers;

    ServerLobbyOrder sendGamesListHandler(const Request& request) const;
    ServerLobbyOrder joinHandler(const Request& request);
    ServerLobbyOrder createHandler(const Request& request);
    ServerLobbyOrder disconnectHandler(const Request& request);

public:
    explicit ServerLobbyProtocol();

    ServerLobbyProtocol(const ServerLobbyProtocol&) = delete;
    ServerLobbyProtocol& operator=(const ServerLobbyProtocol&) = delete;
    ServerLobbyProtocol(ServerLobbyProtocol&&) = delete;
    ServerLobbyProtocol& operator=(ServerLobbyProtocol&&) = delete;

    ServerLobbyOrder handleRequest(const Request& request);


    void end();
};