//
// Created by lionel on 26/05/25.
//

#ifndef TILE_H
#define TILE_H
#include <cstdint>

class Tile {
    uint8_t code;

public:
    Tile(uint8_t code): code(code) {}
    const uint8_t& getCode() const { return this->code; }
};
#endif  // TILE_H
