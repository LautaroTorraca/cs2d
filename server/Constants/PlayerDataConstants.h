#pragma once

#include <string>
#include <vector>
#include "weaponConstants.h"
#include "TeamConstants.h"

struct Coords {
    int16_t x;
    int16_t y;
};

struct Stats {
    int32_t money;
    int16_t life;
};

struct Knife {
    bool hasKnife;
    bool equipped;
};

struct PrimaryWeaponDTO {
    WeaponId weapon;
    int16_t ammo;
    bool equipped;
};

struct SecondaryWeaponDTO {
    WeaponId weapon;
    int16_t ammo;
    bool equipped;
};

struct Inventory {
    Knife knife;
    PrimaryWeaponDTO primaryWeapon;
    SecondaryWeaponDTO secondaryWeapon;
    bool bomb;
};

struct PlayerData {
    std::string nombre;
    std::string id;
    Coords coords;
    Inventory inventory;
    Stats stats;
    Team team;
};

struct Snapshot {
    std::vector<PlayerData> players;
    int yourId;
};



