//
// Created by lionel on 01/06/25.
//

#ifndef RECHARGEABLEWEAPON_H
#define RECHARGEABLEWEAPON_H
#include "DistanceWeapon.h"

class RechargeableWeapon : public DistanceWeapon {
protected:
    uint16_t ammo;
    double weaponDamagePerBullet;
    double weaponPrecision;
    double weaponRange;
    double weaponCadence;
    double weaponSpeed;
    int weaponBulletsPerShot;
    uint16_t maxBullets;
    double lastShotTime;
    bool checkedAttack();
public:
    explicit RechargeableWeapon(const uint16_t& ammo, const double& weaponDamagePerBullet,
        const double& weaponPrecision,
        const double& weaponRange,
        const double& weaponCadence,
        const double& weaponSpeed,
        const int& weaponBulletsPerShot,
        const uint16_t& maxBullets) :
    ammo(ammo),
    weaponDamagePerBullet(weaponDamagePerBullet),
    weaponPrecision(weaponPrecision),
    weaponRange(weaponRange),
    weaponCadence(weaponCadence),
    weaponSpeed(weaponSpeed),
    weaponBulletsPerShot(weaponBulletsPerShot),
    maxBullets(maxBullets),
    lastShotTime(0) {}
    RechargeableWeapon(RechargeableWeapon&& other) noexcept;
    void recharge(uint16_t &amount) override;
};



#endif //RECHARGEABLEWEAPON_H
