//
// Created by lionel on 01/06/25.
//

#pragma once
#include "server/Constants/MapTypeConstants.h"
#include "PlayerChoicesDTO.h"
#include "server/Lobby/GameLobbyStatus.h"

#define BLANK ""

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
