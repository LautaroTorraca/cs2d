//
// Created by lionel on 23/05/25.
//

#include "AwpFactory.h"

#include "Awp.h"

std::unique_ptr<Product> AwpFactory::getProduct(const uint16_t&) {
    double awpDamagePerBullet =
            this->weaponsInfo.getWeaponInfo(WeaponType::AWP, DAMAGE_PER_BULLET_KEY);
    double awpPrecision = this->weaponsInfo.getWeaponInfo(WeaponType::AWP, PRECISION_KEY);
    double awpRange = this->weaponsInfo.getWeaponInfo(WeaponType::AWP, RANGE_KEY);
    double awpCadence = this->weaponsInfo.getWeaponInfo(WeaponType::AWP, CADENCE_KEY);
    double awpSpeed = this->weaponsInfo.getWeaponInfo(WeaponType::AWP, SPEED_KEY);
    double awpBulletsPerShot =
            this->weaponsInfo.getWeaponInfo(WeaponType::AWP, BULLETS_PER_SHOT_KEY);
    return std::make_unique<Awp>(this->cost, awpDamagePerBullet, awpPrecision, awpRange, awpCadence,
                                 awpSpeed, awpBulletsPerShot);
}
