//
// Created by lionel on 01/06/25.
//

#ifndef LOBBY_H
#define LOBBY_H
#include <map>
#include <string>

#include "GameLobby.h"
#include "server/Constants/MapTypeConstants.h"

class Lobby {
    std::map<std::string, std::vector<size_t>> gamesLobbies;
    std::map<MapType, std::string> mapsPaths;
    public:
    Lobby();
    GameLobby createGameLobby(const size_t &id, const std::string &gameName, const MapType& map, const uint8_t& rounds);
    [[nodiscard]] std::vector<std::string> listGames() const;
    void joinGame(size_t& id, std::string& gameName);
    ~Lobby() = default;

};



#endif //LOBBY_H
