#pragma once
#include <cstdint>

enum Direction : uint16_t {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3
};

struct DirectionDTO {
    Direction& direction;
};
