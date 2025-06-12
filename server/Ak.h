//
// Created by lionel on 28/05/25.
//

#ifndef AK_H
#define AK_H
#include <cmath>
#include <map>

#include "PrimaryWeapon.h"


class Ak: public PrimaryWeapon {
    double timePerBurstBullet;
    std::vector<double> timesPerBurstBullet;
    std::vector<std::shared_ptr<Projectile>> inQueueBullets;

protected:
    WeaponType getType() override;

public:
    Ak(const uint16_t& cost, const double& weaponDamagePerBullet, const double& weaponPrecision,
       const double& weaponRange, const double& weaponCadence, const double& weaponSpeed,
       const int& weaponBulletsPerShot, const double& akBurstSpeed):
            PrimaryWeapon(cost, weaponDamagePerBullet, weaponPrecision, weaponRange, weaponCadence,
                          weaponSpeed, weaponBulletsPerShot),
            timePerBurstBullet(std::round((1 / akBurstSpeed) * 100.0) / 100.0) {}

    Ak(Ak&& other) noexcept;

    void attack(Positionable& positionable, const Position& actualPosition,
                const double& destination) override;

    void putBulletInQueue(const double& actualTime);

    void addTo(Inventory& inventory) override;

    void advance(const double& actualTime) override;

    ~Ak() override = default;
};


#endif  // AK_H
