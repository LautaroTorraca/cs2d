//
// Created by lionel on 02/06/25.
//

#ifndef PLAYERCHOICESDTO_H
#define PLAYERCHOICESDTO_H
#include <string>

#include "server/Skin.h"
#include "server/Team.h"

struct PlayerChoicesDTO {
    size_t id;
    std::string playerName;
    Team team;
    Skin skin;
    PlayerChoicesDTO(const size_t& id,const std::string& playerName, const Team& team, const Skin& skin) : id(id), playerName(playerName), team(team), skin(skin) {}
    PlayerChoicesDTO(const std::string& playerName, const Team& team, const Skin& skin) : id(0), playerName(playerName), team(team), skin(skin) {}
    PlayerChoicesDTO& operator=(const PlayerChoicesDTO& other) {
        if (this == &other) {
            return *this;
        }
        id = other.id;
        playerName = other.playerName;
        team = other.team;
        skin = other.skin;
        return *this;
    }
};

#endif //PLAYERCHOICESDTO_H
