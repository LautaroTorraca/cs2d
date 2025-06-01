//
// Created by lionel on 28/05/25.
//

#include "Glock.h"

#include <complex>

void Glock::attack(Positionable &positionable, const Position &actualPosition, const double &angle) {
    if (this->weaponCadence == 0 || this->actualTime - this->lastShotTime < 1/this->weaponCadence) return;
    if (this->ammo == 0) return;
    Coordinate direction(std::cos(angle), -std::sin(angle));
    for (int i = 0; i < this->weaponBulletsPerShot; i++) {
        projectiles.emplace_back(std::make_shared<Projectile>(positionable, actualPosition, direction, weaponRange, weaponPrecision, weaponSpeed, weaponDamagePerBullet));
    }
    this->ammo--;
    this->lastShotTime = this->actualTime;
}

WeaponInfoDTO Glock::getInfo() {
    std::vector<ProjectileDTO> projectilesInfo = this->getProjectilesInfo();
    return {this->ammo, WeaponType::GLOCK, projectilesInfo};
}
