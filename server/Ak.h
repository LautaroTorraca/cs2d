//
// Created by lionel on 28/05/25.
//

#ifndef AK_H
#define AK_H
#include "PrimaryWeapon.h"


class Ak : public PrimaryWeapon {
protected:
    WeaponType getType() override;

public:

    Ak(const uint16_t& cost,
        const double& weaponDamagePerBullet,
        const double& weaponPrecision,
        const double& weaponRange,
        const double& weaponCadence,
        const double& weaponSpeed,
        const double& weaponBulletsPerShot) : PrimaryWeapon(cost,
            weaponDamagePerBullet,
            weaponPrecision,
            weaponRange,
            weaponCadence,
            weaponSpeed,
            weaponBulletsPerShot) {}

    Ak(Ak&& other) noexcept;

    void attack(Positionable &positionable, const Position &actualPosition, const Coordinate &destination) override;

    void addTo(Inventory &inventory) override;

    ~Ak() override = default;
};



#endif //AK_H
