#pragma once
#include <map>
#include <vector>

#include "client/DropInformation.h"
#include "client/PlayerInformation.h"
#include "server/GameStatus.h"
#include "server/ProductType.h"

struct PreSnapshot {
    const size_t clientId;
    const std::vector<std::vector<uint8_t>> map;
    std::map<ProductType, double> shopInfo;
    PreSnapshot(): clientId(0) {}
    PreSnapshot(const size_t& clientId, std::vector<std::vector<uint8_t>>& map, std::map<ProductType, double>& shopInfo):
            clientId(clientId), map(std::move(map)), shopInfo(std::move(shopInfo)) {}
};

struct Snapshot {
    GameStatus status;
    uint8_t currentRound;
    uint8_t countersWinsRounds;
    uint8_t terroristsWinsRounds;
    std::vector<PlayerInformation> playersInfo;
    std::vector<DropInformation> dropsInfo;
    CoordinateInformation plantedBombPosition;
    double bombTimer;
    double actualTime;
    uint8_t totalRounds;

    //   inge
    //   ingeniado
    //   liceniero
    //   licing

    Snapshot(const GameStatus& status, const uint8_t& currentRound,
             const uint8_t& countersWinsRounds, const uint8_t& terroristsWinsRounds,
             const std::vector<PlayerInformation>& playersInfo,
             const std::vector<DropInformation>& drops, const CoordinateInformation& bombPosition,
             const double& bombTimer,
             const double& actualTime, const uint8_t& totalRounds):
            status(status),
            currentRound(currentRound),
            countersWinsRounds(countersWinsRounds),
            terroristsWinsRounds(terroristsWinsRounds),
            playersInfo(playersInfo),
            dropsInfo(drops),
            plantedBombPosition(bombPosition),
            bombTimer(bombTimer),
            actualTime(actualTime),
            totalRounds(totalRounds) {}
};
