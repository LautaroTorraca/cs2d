//
// Created by lionel on 01/06/25.
//

#include "Lobby.h"

#include <iostream>
#include <ranges>
#include <stdexcept>


Lobby::Lobby(LobbyAdder& adder) : adder(adder) {
    this->mapsPaths.emplace(MapType::AZTEC_VILLAGE, "../maps/aztec.yaml");
    this->mapsPaths.emplace(MapType::DUST, "../maps/dust.yaml");
    this->mapsPaths.emplace(MapType::TRAINING_ZONE, "../maps/training_zone.yaml");
}

GameLobby Lobby::createGameLobby(const size_t &id, const std::string &gameName, const MapType& map, const uint8_t& rounds, const uint8_t& playersCount) {
    this->adder.add(gameName, id, this->gamesLobbies);
    GameMapParser parser(this->mapsPaths.at(map));
    if ( playersCount > 2 * parser.getMaxPlayersPerTeam()) {
        this->gamesLobbies.erase(gameName);
        throw std::invalid_argument("The selected map cannot accept that amount of players ");
    }
    this->maxPlayers.emplace(gameName, playersCount);
    return GameLobby(this->mapsPaths.at(map), map, gameName, rounds);
}

void Lobby::joinGame(const size_t &id, const std::string &gameName) {
    if (!this->gamesLobbies.contains(gameName) || this->maxPlayers.at(gameName) == this->gamesLobbies.at(gameName).size()) {
        throw std::invalid_argument("You could not connect to the gameLobby");
    }
    this->gamesLobbies.at(gameName).push_back(id);
}
