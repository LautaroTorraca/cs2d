//
// Created by lionel on 28/05/25.
//

#ifndef MOVER_H
#define MOVER_H

#include <memory>

#include "GameLogic/Utils/Coordinate.h"
#include "GameLogic/Weapons/Explosive.h"

#include "Entity.h"


class Positionable {
    public:
    virtual ~Positionable() = default;

    virtual void move(std::shared_ptr<Entity>& entity, const Coordinate &displacement) = 0;
    virtual void remove(const std::shared_ptr<Entity> &entity) = 0;
    virtual void deactivate(Position& position, std::shared_ptr<Deactivator>& deactivator) = 0;
    virtual void plant(std::shared_ptr<Explosive>& explosive, const Position &position) = 0;
};

#endif //MOVER_H
