//
// Created by lionel on 30/05/25.
//

#ifndef AWPPROJECTILE_H
#define AWPPROJECTILE_H
#include "Projectile.h"


class DirectProjectile : public Projectile {
protected:
    double getDamage() override;
public:
    DirectProjectile(Positionable& positionable, const Position& source, const Coordinate& direction, const double& range, const double& precision, const double& speed, const double& damage) :
    Projectile(positionable, source, direction, range, precision, speed, damage) {}
};

#endif //AWPPROJECTILE_H
