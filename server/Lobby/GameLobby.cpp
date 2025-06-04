//
// Created by lionel on 01/06/25.
//

#include "GameLobby.h"

#include <ranges>
#define PLAYER_NAME_INDEX 0
#define PLAYER_TEAM_INDEX 1
#define PLAYER_SKIN_INDEX 2

GameLobby::GameLobby(GameLobby &&other) noexcept :
parser(std::move(other.parser)), gameName(other.gameName),
playersChoices(other.playersChoices), rounds(other.rounds), joinedPlayers(other.joinedPlayers) {
    if (this != &other) {
        other.gameName = "";
        other.playersChoices = std::map<size_t, std::vector<std::variant<std::string, Team, Skin>>>();
        other.rounds = 0;
        other.joinedPlayers = std::map<size_t, bool>();
    }
}

void GameLobby::join(const size_t &playerId) {
    if (this->joinedPlayers.size() >= this->parser.getMaxPlayersPerTeam()*2) return;
    this->joinedPlayers.emplace(playerId, true);
}

void GameLobby::select(const size_t &playerId, const std::string &name, const Team &team, const Skin &skin) {
    if (!this->joinedPlayers.contains(playerId)) return;
    this->playersChoices[playerId] = {name, team, skin};
    if (this->playersChoices.size() == this->joinedPlayers.size()) {
        this->status = READY_STATUS;
    }
}

GameLobbyDTO GameLobby::getInfo() const {
    std::vector<PlayerChoicesDTO> playersChoices;
    if (this->playersChoices.size() == this->joinedPlayers.size()) {
        for (const auto &[id,playerChoices] : this->playersChoices) {
            playersChoices.emplace_back(id,std::get<std::string>(playerChoices.at(PLAYER_NAME_INDEX)),
                std::get<Team>(playerChoices.at(PLAYER_TEAM_INDEX)),
                std::get<Skin>(playerChoices.at(PLAYER_SKIN_INDEX)));
        }
    }
    return GameLobbyDTO{this->status, playersChoices, this->gameName, this->rounds, this->mapPath, this->mapType};
}

void GameLobby::kick(const size_t &id) {
    if (!this->joinedPlayers.contains(id)) return;
    this->joinedPlayers.erase(id);
    this->playersChoices.erase(id);
    if (this->playersChoices.size() == this->joinedPlayers.size()) {
        this->status = READY_STATUS;
    }
}
