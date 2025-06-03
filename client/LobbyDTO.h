//
// Created by lionel on 03/06/25.
//

#ifndef LOBBYDTO_H
#define LOBBYDTO_H
#include <string>

#include "server/Constants/MapTypeConstants.h"

struct  LobbyDTO {
    const std::string gameName;
    const MapType mapType;
    const uint8_t playersCount;
    const uint8_t rounds;
    LobbyDTO(const std::string& gameName, const MapType& mapType, const uint8_t& playersCount, const uint8_t& rounds) :
    gameName(gameName), mapType(mapType), playersCount(playersCount), rounds(rounds) {}
    LobbyDTO(const std::string& gameName) :
    LobbyDTO(gameName, MapType::DUMMY, 0, 0) {}
};

#endif //LOBBYDTO_H
