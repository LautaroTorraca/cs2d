//
// Created by lionel on 26/05/25.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "GameLogic/Utils/Position.h"

#include "Collisionable.h"

class Entity : public Collisionable {
    public:
    using Collisionable::collision;
    virtual ~Entity() = default;
    virtual Position displaced(const Coordinate & coordinate) = 0;
    virtual void collision(Entity& other) = 0;
    virtual void allocate(const Position& position) = 0;
};

#endif //ENTITY_H
