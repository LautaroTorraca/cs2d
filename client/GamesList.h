//
// Created by lionel on 03/06/25.
//

#ifndef GAMESLIST_H
#define GAMESLIST_H
#include <string>
#include <vector>

struct GamesList {
    std::vector<std::string> games;
    GamesList(std::vector<std::string>& games) : games(games) {}
};

#endif //GAMESLIST_H
