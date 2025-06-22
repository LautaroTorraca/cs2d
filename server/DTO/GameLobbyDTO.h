//
// Created by lionel on 01/06/25.
//

#pragma once
#include <vector>

#include "server/Constants/MapTypeConstants.h"
#include "server/Lobby/GameLobbyStatus.h"

#include "PlayerChoicesDTO.h"

#define BLANK ""

#include "PlayerChoicesDTO.h"

struct GameLobbyDTO {
    GameLobbyStatus status;
    std::vector<PlayerChoicesDTO> playersChoices;
    std::string gameName;
    uint8_t rounds;
    std::string mapPath;
    MapType mapType;
    uint8_t maxPlayers;
    GameLobbyDTO(const GameLobbyStatus& status, const std::vector<PlayerChoicesDTO>& playersChoices,
                 const std::string& gameName, const uint8_t& rounds, const std::string& mapPath,
                 const MapType& mapType, const uint8_t& maxPlayers):
            status(status),
            playersChoices(playersChoices),
            gameName(gameName),
            rounds(rounds),
            mapPath(mapPath),
            mapType(mapType),
            maxPlayers(maxPlayers) {}
    GameLobbyDTO(const GameLobbyStatus& status, std::vector<PlayerChoicesDTO>& playersChoices,
                 const std::string& gameName, const uint8_t& rounds, const MapType& mapType):
            GameLobbyDTO(status, playersChoices, gameName, rounds, BLANK, mapType, 0) {}
    GameLobbyDTO(const std::string& gameName, const uint8_t& rounds, const MapType& mapType, const uint8_t& maxPlayers):
            GameLobbyDTO(INVALID_STATUS, std::vector<PlayerChoicesDTO>(), gameName, rounds, BLANK, mapType, maxPlayers) {}
    GameLobbyDTO& operator=(const GameLobbyDTO& other) {
        if (this == &other) {
            return *this;
        }
        this->status = other.status;
        this->playersChoices = other.playersChoices;
        this->gameName = other.gameName;
        this->rounds = other.rounds;
        this->mapPath = other.mapPath;
        this->mapType = other.mapType;
        this->maxPlayers = other.maxPlayers;
        return *this;

    }
};
