//
// Created by lionel on 31/05/25.
//

#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <cstdint>

enum GameStatus : uint8_t {
    BUY_TIME = 0,
    ON_GOING = 1,
    BOMB_PLANTED = 2,
    TERRORISTS_WIN = 3,
    COUNTERS_WIN = 4,
    BOMB_EXPLODED = 5,
    GAME_OVER = 6
};

#endif  // GAMESTATUS_H
