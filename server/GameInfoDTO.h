//
// Created by lionel on 31/05/25.
//

#ifndef GAMEINFODTO_H
#define GAMEINFODTO_H
#include "DropDTO.h"
#include "GameStatus.h"
#include "PlayerInfoDTO.h"


class GameInfoDTO {
    GameStatus status;
    uint8_t currentRound;
    uint8_t countersWinsRounds;
    uint8_t terroristsWinsRounds;
    std::vector<PlayerInfoDTO> playersInfo;
    std::vector<DropDTO> dropsInfo;
    CoordinateDTO plantedBombPosition;

public:
    explicit GameInfoDTO(const GameStatus& status, const uint8_t& currentRound,
                         const uint8_t& countersWinsRounds, const uint8_t& terroristsWinsRounds,
                         std::vector<PlayerInfoDTO>& playersInfo, std::vector<DropDTO>& dropsInfo,
                         const CoordinateDTO& plantedBombPosition):
            status(status),
            currentRound(currentRound),
            countersWinsRounds(countersWinsRounds),
            terroristsWinsRounds(terroristsWinsRounds),
            playersInfo(std::move(playersInfo)),
            dropsInfo(std::move(dropsInfo)),
            plantedBombPosition(plantedBombPosition) {}
    [[nodiscard]] const GameStatus& getStatus() const;
    [[nodiscard]] const uint8_t& getCurrentRound() const;
    [[nodiscard]] const uint8_t& getCountersWinsRounds() const;
    [[nodiscard]] const uint8_t& getTerroristsWinsRounds() const;
    [[nodiscard]] const std::vector<PlayerInfoDTO>& getPlayersInfo() const;
    [[nodiscard]] const std::vector<DropDTO>& getDropsInfo() const;
    [[nodiscard]] const CoordinateDTO& getPlantedBombPosition() const;
};


#endif  // GAMEINFODTO_H
