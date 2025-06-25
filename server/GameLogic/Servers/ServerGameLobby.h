#pragma once

#include <functional>
#include <map>
#include <memory>

#include "DTO/GamesListDTO.h"
#include "Interfaces/GameLobbyProtocolInterface.h"
#include "Lobby/GameLobby.h"
#include "Orders/GameLobbyOrder.h"
#include "Orders/ServerLobbyOrder.h"
#include "ServerInGame.h"

class ServerGameLobby {
    std::map<OrderType, std::function<void(GameLobbyOrder&)>> translator;
    std::map<std::string, GameLobby> gameLobbies;
    std::map<size_t, std::string> playersToLobby;
    ServerInGame& serverInGame;
    GameLobbyProtocolInterface& protocol;
    const std::function<void(const size_t&)> eraser;
    void setupTranslators();
    void deleteAndCreate(GameLobbyDTO& gameLobbyInfo);

public:

    ServerGameLobby(ServerInGame& serverInGame, GameLobbyProtocolInterface& protocol, const std::function<void(const size_t&)>& eraser);

    void ready(const GameLobbyOrder & order);

    void handle(const std::unique_ptr<Order>& order) const;

    void add(const std::string& gameName, GameLobby& gameLobby);

    void join(const std::string& gameName, const size_t& playerId);

    void exit(const GameLobbyOrder & order);

    GamesListDTO listLobbies(const size_t& id);
};
