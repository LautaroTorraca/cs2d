//
// Created by lionel on 30/05/25.
//

#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H

class Explosive {
public:
    virtual ~Explosive() = default;
    virtual void deactivate() = 0;
    virtual void activate() = 0;
    virtual void continueActivation(const double& actualTime) = 0;
};

#endif //EXPLOSIVE_H
