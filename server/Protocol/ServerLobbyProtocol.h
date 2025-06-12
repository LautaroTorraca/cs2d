#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "Handlers/LobbyHandler.h"
#include "Orders/ServerLobbyOrder.h"
#include "Requests/Request.h"

class ServerLobbyProtocol {
    std::map<size_t, std::unique_ptr<Socket>>& connectedUsers;
    std::map<std::string, size_t> games;
    std::map<uint8_t, std::function<ServerLobbyOrder(const Request&)>> requestHandlers;

    ServerLobbyOrder sendGamesListHandler(const Request& request) const;
    ServerLobbyOrder joinHandler(const Request& request);
    ServerLobbyOrder createHandler(const Request& request);
    ServerLobbyOrder disconnectHandler(const Request& request);

public:
    explicit ServerLobbyProtocol(std::map<size_t, std::unique_ptr<Socket>>& connectedUsers);

    ServerLobbyProtocol(const ServerLobbyProtocol&) = delete;
    ServerLobbyProtocol& operator=(const ServerLobbyProtocol&) = delete;
    ServerLobbyProtocol(ServerLobbyProtocol&&) = delete;
    ServerLobbyProtocol& operator=(ServerLobbyProtocol&&) = delete;

    ServerLobbyOrder handleRequest(const Request& request);


    void end();
};