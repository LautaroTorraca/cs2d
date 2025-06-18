#pragma once
#include <cstddef>
// #include <iostream>
#include <string>

#include "common/Constants/SnapshotConstants.h"
// #include "server/Game.h"
#include "server/GameStatus.h"
// #include "common/socket.h"
// #include "server/Readers/Reader.h"
// #include "server/Sender/Sender.h"

// #include "MoveConstants.h"
// #include "PositionDTO.h"
#include "Protocol.h"
// #include "Protocol.h"
// #include "WeaponChanger.h"

class LobbyDTO;

class ProtocolTesting: public Protocol {
    // Socket clientSocket;
    // Sender sender;
    // Reader reader;
    GameStatus gameStatus = GameStatus::ON_GOING;
    uint8_t currentRound = 3;
    uint8_t countersWins = 1;
    uint8_t terroristsWins = 2;
    std::vector<PlayerInformation> playersInfo;
    std::vector<DropInformation> drops;
    CoordinateInformation bombPosition{0, 0};
    Snapshot snapshot;
    size_t clientID = 1234;

public:
    ProtocolTesting(const std::string& hostName, const std::string& port);
    // void move(const Direction& direction) override;
    // void changeAngle(const PositionDTO& positionInfo) override;
    // void attack() override;
    // void emptyBullets() override;
    // Snapshot receiveSnapshot() const override;
    // PreSnapshot receivePreSnapshot() const override;
    ~ProtocolTesting() {};
};
