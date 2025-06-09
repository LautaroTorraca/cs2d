#pragma once
#include <vector>

#include "server/GameStatus.h"
#include "client/DropInformation.h"
#include "client/PlayerInformation.h"
#include "server/GameStatus.h"

struct PreSnapshot {
    const size_t clientId;
    const std::vector<std::vector<uint8_t>> map;
    PreSnapshot(): clientId(0) {}
    PreSnapshot(const size_t& clientId, std::vector<std::vector<uint8_t>>& map):
            clientId(clientId), map(std::move(map)) {}
};

struct Snapshot {
    GameStatus status;
    uint8_t currentRound;
    uint8_t countersWinsRounds;
    uint8_t terroristsWinsRounds;
    std::vector<PlayerInformation> playersInfo;
    std::vector<DropInformation> dropsInfo;
    CoordinateInformation plantedBombPosition;

    //   inge
    //   ingeniado
    //   liceniero
    //   licing

    Snapshot(const GameStatus& status, const uint8_t& currentRound,
             const uint8_t& countersWinsRounds, const uint8_t& terroristsWinsRounds,
             const std::vector<PlayerInformation>& playersInfo,
             const std::vector<DropInformation>& drops, const CoordinateInformation& bombPosition):
            status(status),
            currentRound(currentRound),
            countersWinsRounds(countersWinsRounds),
            terroristsWinsRounds(terroristsWinsRounds),
            playersInfo(playersInfo),
            dropsInfo(drops),
            plantedBombPosition(bombPosition) {}
};
