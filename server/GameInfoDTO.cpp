//
// Created by lionel on 31/05/25.
//

#include "GameInfoDTO.h"

void GameInfoDTO::setStatus(const GameStatus& status) {
    this->status = status;
}

const GameStatus& GameInfoDTO::getStatus() const {
    return this->status;
}

const uint8_t& GameInfoDTO::getCurrentRound() const {
    return this->currentRound;
}

const uint8_t& GameInfoDTO::getCountersWinsRounds() const {
    return this->countersWinsRounds;
}

const uint8_t& GameInfoDTO::getTerroristsWinsRounds() const {
    return this->terroristsWinsRounds;
}

const std::vector<PlayerInfoDTO> & GameInfoDTO::getPlayersInfo() const {
    return this->playersInfo;
}

const std::vector<DropDTO> & GameInfoDTO::getDropsInfo() const {
    return this->dropsInfo;
}

const CoordinateDTO& GameInfoDTO::getPlantedBombPosition() const {
    return this->plantedBombPosition;
}
const double& GameInfoDTO::getBombTimer() const {
    return this->bombTimer;
}

const double& GameInfoDTO::getElapsedTime() const { return this->elapsedTime; }

const uint8_t& GameInfoDTO::getRounds() const { return this->rounds; }
