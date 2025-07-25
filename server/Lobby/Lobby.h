//
// Created by lionel on 01/06/25.
//

#ifndef LOBBY_H
#define LOBBY_H
#include <map>
#include <string>

#include "common/Constants/MapTypeConstants.h"

#include "GameLobby.h"

class Lobby {
    std::map<std::string, std::vector<size_t>> gamesLobbies;
    std::map<MapType, std::string> mapsPaths;
    std::map<std::string, uint8_t> maxPlayers;
    std::map<size_t, std::string> clientToLobby;

public:
    explicit Lobby();
    GameLobby createGameLobby(const size_t &id, const std::string &gameName, const MapType& map, const uint8_t& rounds, const uint8_t& playersCount);
    void joinGame(const size_t& id, const std::string& gameName);
    ~Lobby() = default;
    void erase(const size_t& id);
    void erase(const std::string& gameName);
};



#endif //LOBBY_H
