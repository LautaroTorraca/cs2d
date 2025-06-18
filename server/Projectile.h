//
// Created by lionel on 28/05/25.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Advancer.h"
#include "Entity.h"
#include "Owner.h"
#include "Positionable.h"
#include "ProjectileDTO.h"

#define PROJECTILE_DIMENSION 0
#define MAX_DEVIATION_GRADES 45

class Projectile : public Entity, public Advancer, public Damager {
    Positionable& positionable;
    const Position& throwerPosition;
    Position startPosition;
    Position position;
    Coordinate direction;
    double actualTime;
    double range;
    double unprecision;
    double speed;
    bool stopped;
    bool killed;

protected:
    double damagePoints;
    virtual double getDamage();

public:

    Projectile(Positionable& positionable, const Position& source, const Coordinate& direction, const double& range, const double& precision, const double& speed, const double& damage) :
    positionable(positionable),
    throwerPosition(source),
    startPosition(source.getCenter(), PROJECTILE_DIMENSION, PROJECTILE_DIMENSION),
    position(source.getCenter(), PROJECTILE_DIMENSION, PROJECTILE_DIMENSION),
    actualTime(0),
    range(range),
    unprecision(1 - precision),
    speed(speed),
    stopped(false),
    killed(false),
    damagePoints(damage)
     {
        this->direction.update(direction);
    }

    Position displaced(const Coordinate &coordinate) override;

    void collision() override;

    void collision(Entity &other) override;

    void collision(Damager &other) override;

    void collision(Damageable &other) override;

    void allocate(const Position &position) override;

    void advance(const double &actualTime) override;

    void damage(uint8_t &healthPoints) override;

    void erase(std::vector<std::shared_ptr<Projectile>> &projectiles, std::shared_ptr<Owner>& owner);

    [[nodiscard]] ProjectileDTO getInfo() const;

};



#endif //PROJECTILE_H
