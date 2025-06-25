//
// Created by lionel on 30/05/25.
//

#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H
#include "GameLogic/Interfaces/Deactivator.h"

class Explosive {
public:
    virtual ~Explosive() = default;
    virtual void deactivate(std::shared_ptr<Deactivator>& deactivator) = 0;
    virtual void activate() = 0;
    virtual void continueActivation(const double& actualTime) = 0;
    virtual double getTime() = 0;
};

#endif //EXPLOSIVE_H
