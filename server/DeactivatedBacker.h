//
// Created by lionel on 26/05/25.
//

#ifndef DEACTIVATEDBACKER_H
#define DEACTIVATEDBACKER_H

#include "Backer.h"
#include "Position.h"

class DeactivatedBacker : public Backer {
    public:
    void pushBack(Position&) override {}

};



#endif //DEACTIVATEDBACKER_H
