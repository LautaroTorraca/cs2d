//
// Created by lionel on 28/05/25.
//

#include "Projectile.h"

Position Projectile::displaced(const Coordinate &) {
    return Position();
}

void Projectile::collision() {
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

void Projectile::allocate(const Position &) {
}

void Projectile::advance(double &) {

}

void Projectile::damage(uint8_t &) {
}
