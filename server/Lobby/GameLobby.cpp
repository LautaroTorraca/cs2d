//
// Created by lionel on 01/06/25.
//

#include "GameLobby.h"

#include <ranges>

#include "server/Constants/MapTypeConstants.h"
#define PLAYER_NAME_INDEX 0
#define PLAYER_TEAM_INDEX 1
#define PLAYER_SKIN_INDEX 2

#define TEAM_TERRORIST 0
#define TEAM_COUNTER 1

GameLobby::GameLobby(GameLobby &&other) noexcept :
parser(std::move(other.parser)), mapPath(std::move(other.mapPath)), mapType(other.mapType), gameName(std::move(other.gameName)),
playersChoices(std::move(other.playersChoices)), rounds(other.rounds),
joinedPlayers(std::move(other.joinedPlayers)), status(other.status), teams(std::move(other.teams)),
maxPlayers(other.maxPlayers) {
    if (this != &other) {
        other.gameName = "";
        other.mapPath = "";
        other.mapType = MapType::DUMMY;
        other.playersChoices = std::map<size_t, std::vector<std::variant<std::string, Team, Skin>>>();
        other.rounds = 0;
        other.joinedPlayers = std::map<size_t, bool>();
        other.status = INVALID_STATUS;
        other.teams = std::array<std::vector<size_t>, 2>();
        other.maxPlayers = 0;
    }
}

void GameLobby::join(const size_t& playerId) {
    if (this->joinedPlayers.size() >= this->parser.getMaxPlayersPerTeam() * 2)
        return;
    this->joinedPlayers.emplace(playerId, true);
}

bool GameLobby::canStart() const {
    return !this->teams.at(TERRORISTS).empty() && !this->teams.at(COUNTER_TERRORISTS).empty() && this->playersChoices.size() == this->joinedPlayers.size();
}

void GameLobby::select(const size_t &playerId, const std::string &name, const Team &team, const Skin &skin) {
    if (!this->joinedPlayers.contains(playerId)) return;
    if (this->teams[team].size() == this->parser.getMaxPlayersPerTeam()) return;
    this->playersChoices[playerId] = {name, team, skin};
    this->teams.at(team).push_back(playerId);
    if (this->canStart()) {
        this->status = READY_STATUS;
    }
}

GameLobbyDTO GameLobby::getInfo() const {
    std::vector<PlayerChoicesDTO> playersChoices;
    for (const auto &[id,playerChoices] : this->playersChoices) {
        playersChoices.emplace_back(id,std::get<std::string>(playerChoices.at(PLAYER_NAME_INDEX)),
            std::get<Team>(playerChoices.at(PLAYER_TEAM_INDEX)),
            std::get<Skin>(playerChoices.at(PLAYER_SKIN_INDEX)));
    }
    return GameLobbyDTO{this->status, playersChoices, this->gameName, this->rounds, this->mapPath, this->mapType, this->maxPlayers};
}

void GameLobby::kick(const size_t& id) {
    if (!this->joinedPlayers.contains(id))
        return;
    this->joinedPlayers.erase(id);
    this->playersChoices.erase(id);
    if (this->canStart()) {
        this->status = READY_STATUS;
    }
}
