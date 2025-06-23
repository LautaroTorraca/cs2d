//
// Created by lionel on 23/06/25.
//

#ifndef COLLISIONABLE_H
#define COLLISIONABLE_H
#include "Damageable.h"
#include "Damager.h"


class Collisionable {
public:
    virtual ~Collisionable() = default;
    virtual void collision() = 0;
    virtual void collision(Damager& damager) = 0;
    virtual void collision(Damageable& damageable) = 0;
};

#endif //COLLISIONABLE_H
