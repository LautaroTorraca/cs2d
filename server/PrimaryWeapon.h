//
// Created by lionel on 28/05/25.
//

#ifndef PRIMARYWEAPON_H
#define PRIMARYWEAPON_H
#include "Product.h"
#include "Projectile.h"
#include "RechargeableWeapon.h"

#define PRIMARY_INDEX 2
#define INITIAL_AMMO 30

class PrimaryWeapon: public Product, public RechargeableWeapon {
protected:
    virtual WeaponType getType() = 0;

public:
    explicit PrimaryWeapon(const uint16_t& cost, const double& weaponDamagePerBullet,
                           const double& weaponPrecision, const double& weaponRange,
                           const double& weaponCadence, const double& weaponSpeed,
                           const int& weaponBulletsPerShot):
            Product(cost),
            RechargeableWeapon(INITIAL_AMMO, weaponDamagePerBullet, weaponPrecision, weaponRange,
                               weaponCadence, weaponSpeed, weaponBulletsPerShot) {}
    PrimaryWeapon(PrimaryWeapon&& other) noexcept:
            Product(std::move(other)), RechargeableWeapon(std::move(other)) {}
    WeaponInfoDTO getInfo() override;
};


#endif  // PRIMARYWEAPON_H
