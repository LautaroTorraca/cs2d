#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Interfaces/GameLobbyProtocolInterface.h"
#include "ServerInGame.h"
#include "Orders/ServerLobbyOrder.h"
#include "Lobby/GameLobby.h"
#include "Orders/GameLobbyOrder.h"

class ServerGameLobby {
    std::map<OrderType, std::function<void(GameLobbyOrder&)>> translator;
    std::map<std::string, GameLobby> gameLobbies;
    std::map<size_t, std::string> playersToLobby;
    ServerInGame& serverInGame;
    GameLobbyProtocolInterface& protocol;
    void setupTranslators();

public:

    ServerGameLobby(ServerInGame& serverInGame, GameLobbyProtocolInterface& protocol);

    void ready(const GameLobbyOrder & order);

    void handle(const std::unique_ptr<Order>& order) const;

    void add(const std::string& gameName, GameLobby& gameLobby);

    void join(const std::string & gameName, const size_t & playerId);

    void exit(const GameLobbyOrder & order);

    std::vector<std::string> listLobbies();
};
