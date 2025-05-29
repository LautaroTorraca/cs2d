#pragma once
#include <cstdint>

enum Direction : uint16_t {
    Up = 0x00,
    Right = 0x01,
    Down = 0x02,
    Left = 0x03
};

struct DirectionDTO {
    Direction& direction;
};
