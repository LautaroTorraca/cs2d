//
// Created by lionel on 01/06/25.
//

#ifndef GAMESLISTDTO_H
#define GAMESLISTDTO_H
#include <string>
#include <vector>

struct GamesListDTO {
    const size_t id;
    const std::vector<std::string> games;
    explicit GamesListDTO(const size_t& id, std::vector<std::string>& games) : id(id), games(std::move(games)) {};

};

#endif //GAMESLISTDTO_H
