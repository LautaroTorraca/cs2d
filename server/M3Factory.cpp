//
// Created by lionel on 24/05/25.
//

#include "M3Factory.h"
#include "M3.h"

#define M3_SWEPT_ANGLE_KEY "sweptAngle"

std::unique_ptr<Product> M3Factory::getProduct(const uint16_t &) {
    double m3DamagePerBullet =  this->weaponsInfo.getWeaponInfo(WeaponType::M3, DAMAGE_PER_BULLET_KEY);
    double m3Precision =  this->weaponsInfo.getWeaponInfo(WeaponType::M3, PRECISION_KEY);
    double m3Range =  this->weaponsInfo.getWeaponInfo(WeaponType::M3, RANGE_KEY);
    double m3Cadence =  this->weaponsInfo.getWeaponInfo(WeaponType::M3, CADENCE_KEY);
    double m3Speed =  this->weaponsInfo.getWeaponInfo(WeaponType::M3, SPEED_KEY);
    double m3BulletsPerShot =  this->weaponsInfo.getWeaponInfo(WeaponType::M3, BULLETS_PER_SHOT_KEY);
    double m3SweptAngle = this->weaponsInfo.getWeaponInfo(WeaponType::M3, M3_SWEPT_ANGLE_KEY);
    return std::make_unique<M3>(this->cost, m3DamagePerBullet, m3Precision, m3Range, m3Cadence, m3Speed, m3BulletsPerShot, m3SweptAngle);
}

