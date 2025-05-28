#pragma once
#include <vector>

#include "PlayerDataConstants.h"


struct DroppedWeaponDTO {
    WeaponId weaponId;
    Coords position;
    double angle;
};

struct GameMap {
    std::vector<DroppedWeaponDTO> droppedWeapons;
};

struct Game {
    GameMap map;
    std::vector<PlayerData> players;
};


