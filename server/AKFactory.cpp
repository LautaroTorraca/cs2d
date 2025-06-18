//
// Created by lionel on 23/05/25.
//

#include "AKFactory.h"

#define BURST_SPEED_KEY "burstSpeed"

std::unique_ptr<Product> AKFactory::getProduct(const uint16_t &) {
    double akDamagePerBullet =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, DAMAGE_PER_BULLET_KEY);
    double akPrecision =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, PRECISION_KEY);
    double akRange =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, RANGE_KEY);
    double akCadence =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, CADENCE_KEY);
    double akSpeed =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, SPEED_KEY);
    double akBulletsPerShot =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, BULLETS_PER_SHOT_KEY);
    double akBurstSpeed =  this->weaponsInfo.getWeaponInfo(WeaponType::AK47, BULLETS_PER_SHOT_KEY);
    return std::make_unique<Ak>(this->cost, akDamagePerBullet, akPrecision, akRange, akCadence, akSpeed, akBulletsPerShot, akBurstSpeed);
}
