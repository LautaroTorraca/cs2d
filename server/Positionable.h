//
// Created by lionel on 28/05/25.
//

#ifndef MOVER_H
#define MOVER_H

#include <memory>

#include "Coordinate.h"
#include "Entity.h"


class Positionable {
    public:
    virtual ~Positionable() = default;

    virtual void move(std::shared_ptr<Entity>& entity, const Coordinate &displacement) = 0;
};

#endif //MOVER_H
