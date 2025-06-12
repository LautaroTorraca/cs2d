//
// Created by lionel on 26/05/25.
//

#ifndef RECEIVER_H
#define RECEIVER_H

#include "Damager.h"

class Damageable {
public:
    virtual ~Damageable() = default;

    virtual void receive(Damager& damager) = 0;
    virtual void pushBack() = 0;
};

#endif  // RECEIVER_H
