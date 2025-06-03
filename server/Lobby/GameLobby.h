//
// Created by lionel on 01/06/25.
//

#ifndef GAMELOBBY_H
#define GAMELOBBY_H
#include <variant>

#include "GameLobbyStatus.h"
#include "server/GameMapParser.h"
#include "server/Team.h"
#include "server/DTO/GameLobbyDTO.h"

class GameLobby {
    GameMapParser parser;
    std::string mapPath;
    std::string gameName;
    std::map<size_t, std::vector<std::variant<std::string, Team, Skin>>> playersChoices;
    uint8_t rounds;
    std::map<size_t, bool> joinedPlayers;
    GameLobbyStatus status;
    public:
    GameLobby(const std::string& mapPath, const std::string& gameName, const uint8_t& rounds) :
    parser(mapPath),
    mapPath(mapPath), gameName(gameName),
    rounds(rounds), status(SELECTING_STATUS) {}
    GameLobby(GameLobby&& other) noexcept;
    void join(const size_t& playerId);
    void select(const size_t &playerId, const std::string &name, const Team &team, const Skin &skin);
    GameLobbyDTO getInfo() const;
};



#endif //GAMELOBBY_H
