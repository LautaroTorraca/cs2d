//
// Created by lionel on 31/05/25.
//

#ifndef RELEASER_H
#define RELEASER_H
#include <cstdint>

class Owner {
    public:
    virtual ~Owner() = default;

    virtual void release(const uint8_t& index) = 0;
    virtual void informKill() = 0;
    virtual void noMoreAmmo() = 0;
};
#endif //RELEASER_H
