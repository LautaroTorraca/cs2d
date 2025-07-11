//
// Created by lionel on 01/06/25.
//

#include "RechargeableWeapon.h"

bool RechargeableWeapon::checkedAttack() {
    if (this->lastShotTime > this->actualTime) {
        this->lastShotTime = 0;
    }
    if (this->weaponCadence == 0 || this->actualTime - this->lastShotTime < 1/this->weaponCadence) return false;
    if (this->ammo == 0) {
        this->owner->noMoreAmmo();
        return false;
    }
    return true;
}

RechargeableWeapon::RechargeableWeapon(RechargeableWeapon &&other) noexcept :
DistanceWeapon(std::move(other)),
ammo(other.ammo),
weaponDamagePerBullet(other.weaponDamagePerBullet),
weaponPrecision(other.weaponPrecision),
weaponRange(other.weaponRange),
weaponCadence(other.weaponCadence),
weaponSpeed(other.weaponSpeed),
weaponBulletsPerShot(other.weaponBulletsPerShot),
maxBullets(other.maxBullets),
lastShotTime(other.lastShotTime){
    if ( this != &other ) {
        other.ammo = 0;
        other.weaponDamagePerBullet = 0;
        other.weaponPrecision = 0;
        other.weaponRange = 0;
        other.weaponCadence = 0;
        other.weaponSpeed = 0;
        other.weaponBulletsPerShot = 0;
        other.maxBullets = 0;
        other.lastShotTime = 0;
    }
}

void RechargeableWeapon::recharge(uint16_t &amount) {
    if (this->ammo + amount > this->maxBullets) return;
    this->ammo += amount;
}
