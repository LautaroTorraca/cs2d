//
// Created by lionel on 01/06/25.
//

#include "Lobby.h"

#include <iostream>
#include <ranges>
#include <stdexcept>


Lobby::Lobby() {
    this->mapsPaths.emplace(MapType::AZTEC_VILLAGE, "../maps/aztec.yaml");
    this->mapsPaths.emplace(MapType::DUST, "../maps/dust.yaml");
    this->mapsPaths.emplace(MapType::TRAINING_ZONE, "../maps/training_zone.yaml");
}

GameLobby Lobby::createGameLobby(const size_t &id, const std::string &gameName, const MapType& map, const uint8_t& rounds) {
    if (this->gamesLobbies.contains(gameName)) {
        throw std::invalid_argument("Game already exists");
    }
    this->gamesLobbies[gameName].push_back(id);
    GameMapParser parser(this->mapsPaths.at(map));
    this->maxPlayers.emplace(gameName, 2 * parser.getMaxPlayersPerTeam());
    return GameLobby(this->mapsPaths.at(map), map, gameName, rounds);
}

void Lobby::joinGame(const size_t &id, const std::string &gameName) {
    if (!this->gamesLobbies.contains(gameName) || this->maxPlayers.at(gameName) == this->gamesLobbies.size()) {
        throw std::invalid_argument("You could not connect to the gameLobby");
    }
    this->gamesLobbies.at(gameName).push_back(id);
}
