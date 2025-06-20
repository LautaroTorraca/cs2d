//
// Created by lionel on 28/05/25.
//

#include "M3.h"
#include <cmath>
#include <iostream>

M3::M3(M3 &&other) noexcept : PrimaryWeapon(std::move(other)), m3SweptAngle(other.m3SweptAngle) {
    if (this != &other) {
        other.m3SweptAngle = 0;
    }
}

void M3::attack(Positionable &positionable, const Position &actualPosition, const double &angle) {
    if (!this->checkedAttack()) return;
    double startAngle = this->toRadians(angle + ANGLE_BIAS) - this->toRadians(this->m3SweptAngle / 2);
    double angleBetweenBullets = this->m3SweptAngle / (this->weaponBulletsPerShot - 1);
    double angleBetweenBulletsInRadians = this->toRadians(angleBetweenBullets);
    for (int i = 0; i < this->weaponBulletsPerShot; i++) {
        Coordinate direction(std::cos(startAngle + angleBetweenBulletsInRadians*i), std::sin(startAngle + angleBetweenBulletsInRadians*i));
        projectiles.emplace_back(std::make_shared<Projectile>(positionable, actualPosition, direction, weaponRange,
            weaponPrecision, weaponSpeed, weaponDamagePerBullet));
    }
    this->ammo--;
    this->lastShotTime = this->actualTime;
}

void M3::addTo(Inventory &inventory) {
    std::shared_ptr<Weapon> weapon = std::make_shared<M3>(std::move(*this));
    inventory.add(PRIMARY_INDEX, weapon);
}

WeaponType M3::getType() {
    return WeaponType::M3;
}
