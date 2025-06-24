#pragma once

#include <functional>
#include <map>
#include <memory>

#include "ServerGameLobby.h"
#include "Interfaces/ServerLobbyProtocolInterface.h"
#include "Lobby/Lobby.h"
#include "Orders/ServerLobbyOrder.h"

class ServerLobby {
    ServerLobbyProtocolInterface& protocol;
    ServerGameLobby& gameLobbyserver;
    std::map<OrderType, std::function<void(ServerLobbyOrder&)>> translator;
    Lobby lobby;

    void setupTranslators();

public:

    explicit ServerLobby(ServerLobbyProtocolInterface& protocol, ServerGameLobby& serverGameLobby);

    void handle(const std::unique_ptr<Order>& order) const;
    void createGame(const ServerLobbyOrder& order);
    void joinGame(const ServerLobbyOrder& order);
    void leaveGame(const ServerLobbyOrder& order);
    void listGames(const ServerLobbyOrder& order) const;
    void erase(const size_t& id);
};
