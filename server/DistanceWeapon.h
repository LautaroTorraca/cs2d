//
// Created by lionel on 01/06/25.
//

#ifndef DISTANCEWEAPON_H
#define DISTANCEWEAPON_H
#include "GenericWeapon.h"
#include "Projectile.h"
#include "Weapon.h"
#define ANGLE_BIAS 270
#define PI_TO_GRADES 180

class DistanceWeapon : public GenericWeapon {
protected:
    double actualTime;
    std::vector<std::shared_ptr<Projectile>> projectiles;
    DistanceWeapon() : actualTime(0) {}
    DistanceWeapon( DistanceWeapon&& other) noexcept;
    virtual std::vector<std::shared_ptr<Projectile>> getProjectilesCopy();
    [[nodiscard]] virtual std::vector<ProjectileDTO> getProjectilesInfo() const;

public:
    void advance(const double &actualTime) override;
};



#endif //DISTANCEWEAPON_H
