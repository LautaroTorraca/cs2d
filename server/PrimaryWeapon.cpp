//
// Created by lionel on 28/05/25.
//

#include "PrimaryWeapon.h"

PrimaryWeapon::PrimaryWeapon(PrimaryWeapon &&other) noexcept :
Product(std::move(other)),
ammo(other.ammo),
weaponDamagePerBullet(other.weaponDamagePerBullet),
weaponPrecision(other.weaponPrecision),
weaponRange(other.weaponRange),
weaponCadence(other.weaponCadence),
weaponSpeed(other.weaponSpeed),
weaponBulletsPerShot(other.weaponBulletsPerShot) {
    if ( this != &other ) {
        other.ammo = 0;
        other.weaponDamagePerBullet = 0;
        other.weaponPrecision = 0;
        other.weaponRange = 0;
        other.weaponCadence = 0;
        other.weaponSpeed = 0;
        other.weaponBulletsPerShot = 0;
    }
}

void PrimaryWeapon::recharge(uint16_t &amount) {
    this->ammo += amount;
}

WeaponInfoDTO PrimaryWeapon::getInfo() {
    return {this->ammo, this->getType()};
}
