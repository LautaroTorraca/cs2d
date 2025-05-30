//
// Created by lionel on 28/05/25.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Advancer.h"
#include "Entity.h"
#include "Positionable.h"

#define PROJECTILE_DIMENSION 2
#define MAX_DEVIATION_GRADES 45

class Projectile : public Entity, public Advancer, public Damager {
    Positionable& positionable;
    Position position;
    Coordinate destination;
    double startedTime;
    double actualTime;
    double range;
    double speed;
    double damagePoints;
public:

    Projectile(Positionable& positionable, const Position& source, const Coordinate& destination, const double& range, const double& speed, const double& damage) :
    positionable(positionable),
    position(0,0, PROJECTILE_DIMENSION, PROJECTILE_DIMENSION),
    startedTime(0),
    actualTime(0),
    range(range),
    speed(speed),
    damagePoints(damage) {
        this->position.updateLocationTo(source);
        this->destination.update(destination);
    }

    Position displaced(const Coordinate &coordinate) override;

    void collision() override;

    void collision(Entity &other) override;

    void collision(Damager &other) override;

    void collision(Damageable &other) override;

    void allocate(const Position &position) override;

    void advance(double &actualTime) override;

    void damage(uint8_t &healthPoints) override;

};



#endif //PROJECTILE_H
