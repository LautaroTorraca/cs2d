//
// Created by lionel on 30/05/25.
//

#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H
#include "Advancer.h"

class Explosive : public Advancer {
public:
    
    virtual void deactivate() = 0;
    virtual void activate() = 0;
};

#endif //EXPLOSIVE_H
