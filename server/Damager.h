//
// Created by lionel on 26/05/25.
//

#ifndef DAMAGER_H
#define DAMAGER_H
#include <cstdint>

class Damager {
    public:
    virtual ~Damager() = default;
    virtual void damage(uint8_t& healthPoints) = 0;
};

#endif //DAMAGER_H
