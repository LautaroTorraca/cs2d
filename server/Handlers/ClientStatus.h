//
// Created by lionel on 18/06/25.
//

#ifndef CLIENTSTATUS_H
#define CLIENTSTATUS_H
#include <cstdint>
enum ClientStatus : uint8_t {
    IN_LOBBY = 0,
    IN_GAME_LOBBY = 1,
    IN_GAME = 2
};
#endif //CLIENTSTATUS_H
