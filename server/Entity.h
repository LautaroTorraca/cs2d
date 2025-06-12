//
// Created by lionel on 26/05/25.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "Damageable.h"
#include "Damager.h"
#include "Position.h"


// TODO: Segregar esta intefaz
class Entity {
public:
    virtual ~Entity() = default;
    virtual Position displaced(const Coordinate& coordinate) = 0;
    virtual void collision() = 0;
    virtual void collision(Entity& other) = 0;
    virtual void collision(Damager& damager) = 0;
    virtual void collision(Damageable& damageable) = 0;
    virtual void allocate(const Position& position) = 0;
};

#endif  // ENTITY_H
