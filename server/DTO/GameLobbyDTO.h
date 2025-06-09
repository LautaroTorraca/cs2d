//
// Created by lionel on 01/06/25.
//

#pragma once
#include "server/Constants/MapTypeConstants.h"
#include "PlayerChoicesDTO.h"
#ifndef LOBBYDTO_H
#define LOBBYDTO_H
#include <vector>

#include "server/Constants/MapTypeConstants.h"
#include "server/Lobby/GameLobbyStatus.h"

#define BLANK ""

#include "PlayerChoicesDTO.h"

struct GameLobbyDTO {
    const GameLobbyStatus status;
    const std::vector<PlayerChoicesDTO> playersChoices;
    const std::string gameName;
    const uint8_t rounds;
    const std::string mapPath;
    const MapType mapType;
    GameLobbyDTO(const GameLobbyStatus& status, std::vector<PlayerChoicesDTO>& playersChoices,
        const std::string& gameName, const uint8_t& rounds, const std::string& mapPath, const MapType& mapType) :
    status(status), playersChoices(std::move(playersChoices)), gameName(gameName), rounds(rounds), mapPath(mapPath), mapType(mapType) {}
    GameLobbyDTO(const GameLobbyStatus& status, std::vector<PlayerChoicesDTO>& playersChoices,
        const std::string& gameName, const uint8_t& rounds, const MapType& mapType) :
    GameLobbyDTO(status, playersChoices, gameName, rounds, BLANK,mapType) {}
};
    const MapType mapType;
    GameLobbyDTO(const GameLobbyStatus& status, std::vector<PlayerChoicesDTO>& playersChoices,
                 const std::string& gameName, const uint8_t& rounds, const std::string& mapPath,
                 const MapType& mapType):
            status(status),
            playersChoices(std::move(playersChoices)),
            gameName(gameName),
            rounds(rounds),
            mapPath(mapPath),
            mapType(mapType) {}
};

#endif  // LOBBYDTO_H
