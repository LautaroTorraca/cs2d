//
// Created by lionel on 03/06/25.
//

#ifndef GAMESLIST_H
#define GAMESLIST_H
#include <string>
#include <vector>

struct GamesList {
    std::vector<GameLobbyDTO> gamesLobbies;
    GamesList(std::vector<GameLobbyDTO> gamesLobbies) : gamesLobbies(gamesLobbies) {}
};

#endif  // GAMESLIST_H
