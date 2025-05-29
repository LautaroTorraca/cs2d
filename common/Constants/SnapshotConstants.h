#pragma once
#include "PlayerDataConstants.h"
#include <vector>

struct PreSnapshot {
  std::vector<std::vector<int>> tileMap;
  size_t clientId;
};

struct Snapshot {
  DTO::Game game;
};
