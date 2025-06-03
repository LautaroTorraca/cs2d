#pragma once
#include "PlayerDataConstants.h"
#include <vector>

struct PreSnapshot {
  const size_t clientId;
  const std::vector<std::vector<uint8_t>> map;
  PreSnapshot() : clientId(0) {}
  PreSnapshot(const size_t& clientId, std::vector<std::vector<uint8_t>>& map) : clientId(clientId), map(std::move(map)) {}
};

struct Snapshot {
  DTO::Game game;
};
