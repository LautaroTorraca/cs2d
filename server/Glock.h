//
// Created by lionel on 28/05/25.
//

#ifndef GLOCK_H
#define GLOCK_H

#include "Weapon.h"
#include "Projectile.h"

#include "RechargeableWeapon.h"

#define GLOCK_INITIAL_AMMO 30

class Glock : public RechargeableWeapon {
    public:
    Glock(const double& weaponDamagePerBullet, const double& weaponPrecision, const double& weaponRange, const double& weaponCadence, const double& weaponSpeed, const int& weaponBulletsPerShot) :
    RechargeableWeapon(GLOCK_INITIAL_AMMO, weaponDamagePerBullet, weaponPrecision, weaponRange, weaponCadence, weaponSpeed,weaponBulletsPerShot) {}
    void attack(Positionable &positionable, const Position &actualPosition, const double &angle) override;
    WeaponInfoDTO getInfo() override;

};



#endif //GLOCK_H
