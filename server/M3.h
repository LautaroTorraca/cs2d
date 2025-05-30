//
// Created by lionel on 28/05/25.
//

#ifndef M3_H
#define M3_H
#include "PrimaryWeapon.h"


class M3 : public PrimaryWeapon {
protected:
    WeaponType getType() override;

public:

    M3(M3 &&other) noexcept;

    explicit M3(const uint16_t& cost,
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

    void attack(Positionable &positionable, const Position &actualPosition, const Coordinate &destination) override;

    void addTo(Inventory &inventory) override;

    ~M3() override = default;
};



#endif //M3_H
