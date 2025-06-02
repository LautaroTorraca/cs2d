//
// Created by lionel on 01/06/25.
//

#include "Lobby.h"

#include <ranges>
#include <stdexcept>


Lobby::Lobby() {
    this->mapsPaths.emplace(MapType::AZTEC_VILLAGE, "../../maps/aztec.yaml");
    this->mapsPaths.emplace(MapType::DUST, "../../maps/dust.yaml");
    this->mapsPaths.emplace(MapType::TRAINING_ZONE, "../../maps/training_zone.yaml");
}

GameLobby Lobby::createGameLobby(const size_t &id, const std::string &gameName, const MapType& map, const uint8_t& rounds) {
    if (this->gamesLobbies.contains(gameName)) {
        throw std::invalid_argument("Game already exists");
    }
    this->gamesLobbies[gameName].push_back(id);
    return GameLobby(this->mapsPaths.at(map), gameName, rounds);
}

std::vector<std::string> Lobby::listGames() const {
    std::vector<std::string> games;
    for (const auto &gameName: this->gamesLobbies | std::views::keys) {
        games.emplace_back(gameName);
    }
    return games;
}

void Lobby::joinGame(size_t &id, std::string &gameName) {
    if (!this->gamesLobbies.contains(gameName)) {
        throw std::invalid_argument("Game not exists");
    }
    this->gamesLobbies.at(gameName).push_back(id);
}
