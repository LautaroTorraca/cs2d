//
// Created by lionel on 01/06/25.
//

#ifndef GAMELOBBY_H
#define GAMELOBBY_H
#include <variant>

#include "GameLobbyStatus.h"
#include "server/Constants/MapTypeConstants.h"
#include "server/GameMapParser.h"
#include "server/Team.h"
#include "server/DTO/GameLobbyDTO.h"

class GameLobby {
    GameMapParser parser;
    std::string mapPath;
    MapType mapType;
    std::string gameName;
    std::map<size_t, std::vector<std::variant<std::string, Team, Skin>>> playersChoices;
    uint8_t rounds;
    std::map<size_t, bool> joinedPlayers;
    GameLobbyStatus status;
    std::array<std::vector<size_t>, 2> teams;
    uint8_t maxPlayers;

    [[nodiscard]] bool canStart() const;
    public:
    GameLobby(const std::string& mapPath, const MapType mapType, const std::string& gameName, const uint8_t& rounds, const uint8_t& maxPlayers) :
    parser(mapPath),
    mapPath(mapPath),
    mapType(mapType),
    gameName(gameName),
    rounds(rounds), status(SELECTING_STATUS),
    maxPlayers(maxPlayers) {}
    GameLobby(GameLobby&& other) noexcept;
    void join(const size_t& playerId);
    void select(const size_t &playerId, const std::string &name, const Team &team, const Skin &skin);
    [[nodiscard]] GameLobbyDTO getInfo() const;
    void kick(const size_t& id);
};



#endif //GAMELOBBY_H
