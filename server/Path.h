//
// Created by lionel on 26/05/25.
//

#ifndef PATH_H
#define PATH_H
#include "Tile.h"


class Path : public Tile {
    public:
    explicit Path(const uint8_t& code) : Tile(code) {}

};



#endif //PATH_H
