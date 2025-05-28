#pragma once
#include <vector>

#include "PlayerDataConstants.h"


struct PreSnapshot {
    std::vector<std::vector<int>> tileMap;
    size_t clientId;
};

struct Snapshot {
    std::vector<std::vector<int>> tileMap;
    std::vector<PlayerData> players;
    size_t clientId;

};