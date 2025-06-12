//
// Created by lionel on 26/05/25.
//

#ifndef BACKER_H
#define BACKER_H
#include "Position.h"

class Backer {
public:
    virtual ~Backer() = default;
    virtual void pushBack(Position& positionToUpdate) = 0;
};

#endif  // BACKER_H
