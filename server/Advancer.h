//
// Created by lionel on 20/05/25.
//

#ifndef ADVANCER_H
#define ADVANCER_H

class Advancer {
public:
    virtual ~Advancer() = default;
    virtual void advance(const double& actualTime) = 0;
};

#endif  // ADVANCER_H
