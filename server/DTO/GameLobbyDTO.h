//
// Created by lionel on 01/06/25.
//

#ifndef LOBBYDTO_H
#define LOBBYDTO_H
#include "PlayerChoicesDTO.h"
#include "server/Lobby/GameLobbyStatus.h"

struct GameLobbyDTO {
    const GameLobbyStatus status;
    const std::vector<PlayerChoicesDTO> playersChoices;
    const std::string gameName;
    const uint8_t rounds;
    const std::string mapPath;
    explicit GameLobbyDTO(const GameLobbyStatus& status, std::vector<PlayerChoicesDTO>& playersChoices,
        const std::string& gameName, const uint8_t& rounds, const std::string& mapPath) :
    status(status), playersChoices(std::move(playersChoices)), gameName(gameName), rounds(rounds), mapPath(mapPath) {}
};

#endif //LOBBYDTO_H
