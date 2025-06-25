//
// Created by lionel on 28/05/25.
//

#ifndef AWP_H
#define AWP_H
#include "PrimaryWeapon.h"


class Awp : public PrimaryWeapon {
protected:
    WeaponType getType() override;
public:

    Awp(Awp &&other) noexcept;

    explicit Awp(const uint16_t& cost,
        const double& weaponDamagePerBullet,
        const double& weaponPrecision,
        const double& weaponRange,
        const double& weaponCadence,
        const double& weaponSpeed,
        const int& weaponBulletsPerShot,
        const uint16_t& maxBullets) : PrimaryWeapon(cost,
            weaponDamagePerBullet,
            weaponPrecision,
            weaponRange,
            weaponCadence,
            weaponSpeed,
            weaponBulletsPerShot,
            maxBullets) {}

    void attack(Positionable &positionable, const Position &actualPosition, const double &destination) override;

    void addTo(Inventory &inventory) override;

 ~Awp() override = default;
};



#endif //AWP_H
