//
// Created by lionel on 28/05/25.
//

#include "Projectile.h"

#include "Randomizator.h"
#include <iostream>
#define DAMAGE_REDUCE_CUSHIONING 0.05

Position Projectile::displaced(const Coordinate & coordinate) {
    return this->position + coordinate;
}

void Projectile::collision() {
    this->stopped = true;
}

void Projectile::collision(Entity & entity) {
    Damager& damager = *this;
    entity.collision(damager);
}

void Projectile::collision(Damager &) {}

void Projectile::collision(Damageable & damageable) {
    Damager& damager = *this;
    damageable.receive(damager);
}

void Projectile::allocate(const Position & position) {
    this->position.updateLocationTo(position);
}

void Projectile::advance(const double &actualTime) {
    if (this->actualTime == 0) {
        this->actualTime = actualTime;
    }
    std::shared_ptr<Entity> entity(this, [](Projectile*) { /* no delete */ });
    double traveledDistance = this->position.getCenter().distanceTo(this->startPosition.getCenter());
    Coordinate displacement = this->direction.rotatedIn(this->unprecision*MAX_DEVIATION_GRADES*(traveledDistance/this->range))*this->speed*(actualTime - this->actualTime);
    this->actualTime = actualTime;
    if ( traveledDistance >= this->range ) {
        this->stopped = true;
    }
    this->positionable.move(entity, displacement);
}

double Projectile::getDamage() {
    Randomizator randomizer;
    double damage = randomizer.getRandom(this->damagePoints);
    double totalDamage = damage/(this->position.getCenter().distanceTo(this->startPosition.getCenter())*DAMAGE_REDUCE_CUSHIONING);
    return totalDamage;
}

void Projectile::damage(uint8_t& healthPoints) {
    if(this->position.intersects(this->throwerPosition)) return;
    this->stopped = true;
    double damage = this->getDamage();
    this->damagePoints = 0;
    if (damage > healthPoints) {
        healthPoints = damage;
        this->killed = true;
    }
    healthPoints -= damage;
}

void Projectile::erase(std::vector<std::shared_ptr<Projectile>> &projectiles, std::shared_ptr<Owner>& owner) {
    if (this->killed) owner->informKill();
    if (this->stopped) {
        std::shared_ptr<Projectile> entity((this), [](Projectile*) {  });
        this->positionable.remove(entity);
        std::erase_if(projectiles, [this](const std::shared_ptr<Projectile>& projectile) {return projectile.get() == this;});
    }
}

ProjectileDTO Projectile::getInfo() const {
    return ProjectileDTO(this->position.getPoint());
}
