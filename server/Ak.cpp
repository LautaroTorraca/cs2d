#include "Ak.h"

#include <iostream>

#define RETARDATION 0.1


Ak::Ak(Ak &&other) noexcept : PrimaryWeapon(std::move(other)), timePerBurstBullet(other.timePerBurstBullet) {
    if (this != &other) {
        other.timePerBurstBullet = 0;
    }
}

void Ak::attack(Positionable &positionable, const Position &actualPosition, const double &angle) {
    if (!this->checkedAttack()) return;
    Coordinate direction(std::cos(angle), -std::sin(angle));
    for (int i = 0; i < this->weaponBulletsPerShot; i++) {
        this->timesPerBurstBullet.emplace_back(this->actualTime + this->timePerBurstBullet*i + RETARDATION);
        this->inQueueBullets.emplace_back(
            std::make_shared<Projectile>(positionable, actualPosition, direction, weaponRange,
                weaponPrecision, weaponSpeed, weaponDamagePerBullet));
    }
    this->ammo--;
    this->lastShotTime = this->actualTime;
}

void Ak::putBulletInQueue(const double &actualTime) {
    if (!this->timesPerBurstBullet.empty() && this->timesPerBurstBullet.front() <= actualTime) {
        this->projectiles.emplace_back(this->inQueueBullets.front());
        this->inQueueBullets.erase(this->inQueueBullets.begin());
        this->timesPerBurstBullet.erase(this->timesPerBurstBullet.begin());
    }
}

void Ak::advance(const double &actualTime) {
    this->putBulletInQueue(actualTime);
    PrimaryWeapon::advance(actualTime);
}

void Ak::addTo(Inventory &inventory) {
    std::shared_ptr<Weapon> weapon = std::make_shared<Ak>(std::move(*this));
    inventory.add(PRIMARY_INDEX, weapon);
}

WeaponType Ak::getType() {
    return WeaponType::AK47;
}
