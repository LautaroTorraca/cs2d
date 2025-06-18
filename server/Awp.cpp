//
// Created by lionel on 28/05/25.
//

#include "Awp.h"
#include <cmath>

#include "DirectProjectile.h"

Awp::Awp(Awp &&other) noexcept : PrimaryWeapon(std::move(other)) {
}

void Awp::attack(Positionable &positionable, const Position &actualPosition, const double &angle) {
    if (!this->checkedAttack()) return;
    Coordinate direction(std::cos(angle), -std::sin(angle));
    for (int i = 0; i < this->weaponBulletsPerShot; i++) {
        projectiles.emplace_back(std::make_shared<DirectProjectile>(positionable, actualPosition, direction, weaponRange, weaponPrecision, weaponSpeed, weaponDamagePerBullet));
    }
    this->ammo--;
    this->lastShotTime = this->actualTime;
}

void Awp::addTo(Inventory &inventory) {
    std::shared_ptr<Weapon> weapon = std::make_shared<Awp>(std::move(*this));
    inventory.add(PRIMARY_INDEX, weapon);
}

WeaponType Awp::getType() {
    return WeaponType::AWP;
}
