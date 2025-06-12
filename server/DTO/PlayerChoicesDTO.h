//
// Created by lionel on 02/06/25.
//

#ifndef PLAYERCHOICESDTO_H
#define PLAYERCHOICESDTO_H
#include <string>

#include "server/Skin.h"
#include "server/Team.h"

struct PlayerChoicesDTO {
    const size_t id;
    const std::string playerName;
    const Team team;
    const Skin skin;
    PlayerChoicesDTO(const size_t& id, const std::string& playerName, const Team& team,
                     const Skin& skin):
            id(id), playerName(playerName), team(team), skin(skin) {}
};

#endif  // PLAYERCHOICESDTO_H
