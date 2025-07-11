#pragma once

#include "server/Requests/Request.h"
#include "server/Orders/GameLobbyOrder.h"
#include "server/Handlers/GameLobbyHandler.h"
#include <map>
#include <memory>
#include <functional>

class GameLobbyProtocol {
    std::map<size_t, std::unique_ptr<GameLobbyHandler>> lobbyUsers;

    std::map<uint8_t, std::function<GameLobbyOrder(const Request&)>> requestHandlers;

    GameLobbyOrder readyHandler(const Request& request);
    GameLobbyOrder exitLobbyHandler(const Request& request);

public:
    GameLobbyProtocol();

    GameLobbyProtocol(const GameLobbyProtocol&) = delete;
    GameLobbyProtocol& operator=(const GameLobbyProtocol&) = delete;
    GameLobbyProtocol(GameLobbyProtocol&&) = delete;
    GameLobbyProtocol& operator=(GameLobbyProtocol&&) = delete;

    GameLobbyOrder handleRequest(const Request& request);

    void registerClient(size_t clientId, std::unique_ptr<GameLobbyHandler> handler);
    void end();
};
