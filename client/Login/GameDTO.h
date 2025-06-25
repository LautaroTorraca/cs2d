#pragma once

#include <qt6/QtCore/QString>

#include "common/Constants/MapTypeConstants.h"

class GameDTO {
public:
    QString name;
    MapType mapType;
    uint8_t playerCount;
    uint8_t maxPlayers;
    uint8_t rounds;

    GameDTO() = default;

    GameDTO(const QString& name, MapType mapType, uint8_t playerCount, uint8_t maxPlayers, uint8_t rounds)
            : name(name), mapType(mapType), playerCount(playerCount), maxPlayers(maxPlayers), rounds(rounds) {}
};
