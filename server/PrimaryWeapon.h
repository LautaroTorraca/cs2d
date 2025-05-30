//
// Created by lionel on 28/05/25.
//

#ifndef PRIMARYWEAPON_H
#define PRIMARYWEAPON_H
#include "Product.h"
#include "Weapon.h"

#define PRIMARY_INDEX 2
#define PRIMARY_INITIAL_AMMO 30

class PrimaryWeapon : public Product, public Weapon {
    uint16_t ammo;
    double weaponDamagePerBullet;
    double weaponPrecision;
    double weaponRange;
    double weaponCadence;
    double weaponSpeed;
    double weaponBulletsPerShot;
protected:
    virtual WeaponType getType() = 0;
public:
    explicit PrimaryWeapon(const uint16_t& cost, const double& weaponDamagePerBullet,
        const double& weaponPrecision,
        const double& weaponRange,
        const double& weaponCadence,
        const double& weaponSpeed,
        const double& weaponBulletsPerShot) : Product(cost),
    ammo(PRIMARY_INITIAL_AMMO),
    weaponDamagePerBullet(weaponDamagePerBullet),
    weaponPrecision(weaponPrecision),
    weaponRange(weaponRange),
    weaponCadence(weaponCadence),
    weaponSpeed(weaponSpeed),
    weaponBulletsPerShot(weaponBulletsPerShot) {}
    PrimaryWeapon(PrimaryWeapon&& other) noexcept;
    void recharge(uint16_t &amount) override;

    WeaponInfoDTO getInfo() override;
};



#endif //PRIMARYWEAPON_H
