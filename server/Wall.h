//
// Created by lionel on 27/05/25.
//

#ifndef WALL_H
#define WALL_H
#include "Tile.h"


class Wall : public Tile {
public:
    explicit Wall(const uint8_t& code) : Tile(code) {}

};


#endif //WALL_H
