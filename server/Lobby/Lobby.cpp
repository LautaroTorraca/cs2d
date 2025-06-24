//
// Created by lionel on 01/06/25.
//

#include "Lobby.h"

#include <iostream>
#include <ranges>
#include <stdexcept>

#include "GameAlreadyExistsException.h"
#include "Player.h"


Lobby::Lobby() {
    this->mapsPaths.emplace(MapType::AZTEC_VILLAGE, "../maps/aztec.yaml");
    this->mapsPaths.emplace(MapType::DUST, "../maps/dust.yaml");
    this->mapsPaths.emplace(MapType::TRAINING_ZONE, "../maps/training_zone.yaml");
}

GameLobby Lobby::createGameLobby(const size_t &id, const std::string &gameName, const MapType& map, const uint8_t& rounds, const uint8_t& playersCount) {
    if (this->gamesLobbies.contains(gameName)) {
        throw GameAlreadyExistsException("The gameName already exists");
    }
    this->gamesLobbies[gameName].push_back(id);
    GameMapParser parser(this->mapsPaths.at(map));
    if ( playersCount > 2 * parser.getMaxPlayersPerTeam()) {
        this->gamesLobbies.erase(gameName);
        throw std::invalid_argument("The selected map cannot accept that amount of players ");
    }
    this->maxPlayers.emplace(gameName, playersCount);
    this->clientToLobby.emplace(id, gameName);
    return GameLobby(this->mapsPaths.at(map), map, gameName, rounds, this->maxPlayers.at(gameName));
}

void Lobby::joinGame(const size_t& id, const std::string& gameName) {
    if (!this->gamesLobbies.contains(gameName) ||
        this->maxPlayers.at(gameName) == this->gamesLobbies.at(gameName).size()) {
        throw std::invalid_argument("You could not connect to the gameLobby");
    }
    this->gamesLobbies.at(gameName).push_back(id);
    this->clientToLobby.emplace(id, gameName);
}
void Lobby::erase(const size_t& id) {
    if (!this->clientToLobby.contains(id))
        return;
    std::string gameName = this->clientToLobby.at(id);
    this->clientToLobby.erase(id);
    std::erase(this->gamesLobbies.at(gameName), id);
    if (this->gamesLobbies.at(gameName).empty()) {
        this->gamesLobbies.erase(gameName);
        this->maxPlayers.erase(gameName);
    }
}

void Lobby::erase(const std::string& gameName) {
    if (!this->gamesLobbies.contains(gameName)) return;
    for (const auto& id: this->gamesLobbies.at(gameName)) {
        this->clientToLobby.erase(id);
    }
    this->gamesLobbies.erase(gameName);
    this->maxPlayers.erase(gameName);
}
