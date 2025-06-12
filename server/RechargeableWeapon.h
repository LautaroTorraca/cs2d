//
// Created by lionel on 01/06/25.
//

#ifndef RECHARGEABLEWEAPON_H
#define RECHARGEABLEWEAPON_H
#include "DistanceWeapon.h"

class RechargeableWeapon: public DistanceWeapon {
protected:
    uint16_t ammo;
    double weaponDamagePerBullet;
    double weaponPrecision;
    double weaponRange;
    double weaponCadence;
    double weaponSpeed;
    int weaponBulletsPerShot;
    double lastShotTime;
    bool checkedAttack() const;

public:
    explicit RechargeableWeapon(const uint16_t& ammo, const double& weaponDamagePerBullet,
                                const double& weaponPrecision, const double& weaponRange,
                                const double& weaponCadence, const double& weaponSpeed,
                                const int& weaponBulletsPerShot):
            ammo(ammo),
            weaponDamagePerBullet(weaponDamagePerBullet),
            weaponPrecision(weaponPrecision),
            weaponRange(weaponRange),
            weaponCadence(weaponCadence),
            weaponSpeed(weaponSpeed),
            weaponBulletsPerShot(weaponBulletsPerShot),
            lastShotTime(0) {}
    RechargeableWeapon(RechargeableWeapon&& other) noexcept;
    void recharge(uint16_t& amount) override;
};


#endif  // RECHARGEABLEWEAPON_H
