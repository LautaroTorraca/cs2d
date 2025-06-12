#pragma once

#include <QString>

class CreateGameDTO {
public:
    QString playerName;
    QString team;
    uint8_t skinId;
    int playerCount;
    int maxPlayers;
    int rounds;
};
