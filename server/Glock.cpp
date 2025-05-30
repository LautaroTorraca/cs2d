//
// Created by lionel on 28/05/25.
//

#include "Glock.h"

void Glock::attack(Positionable &positionable, const Position &actualPosition, const Coordinate &destination) {
    projectiles.emplace_back(positionable, actualPosition, destination, glockRange, glockSpeed, glockDamagePerBullet);
}

void Glock::recharge(uint16_t &amount) {
    this->ammo += amount;
}

WeaponInfoDTO Glock::getInfo() {
    return {this->ammo, WeaponType::GLOCK};
}
