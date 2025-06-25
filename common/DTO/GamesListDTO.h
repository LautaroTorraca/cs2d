//
// Created by lionel on 01/06/25.
//

#ifndef GAMESLISTDTO_H
#define GAMESLISTDTO_H
#include <string>
#include <vector>

#include "GameLobbyDTO.h"

struct GamesListDTO {
    const size_t id;
    std::vector<GameLobbyDTO> gamesLobbies;
    GamesListDTO(const size_t& id, std::vector<GameLobbyDTO>& gamesLobbies) : id(id), gamesLobbies(std::move(gamesLobbies)) {};

};

#endif //GAMESLISTDTO_H
