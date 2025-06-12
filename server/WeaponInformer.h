//
// Created by lionel on 28/05/25.
//

#ifndef WEAPONINFORMER_H
#define WEAPONINFORMER_H
#include <string>

#include "WeaponConstants.h"

#define MIN_DAMAGE_KEY "minDamage"
#define MAX_DAMAGE_KEY "maxDamage"
#define RANGE_KEY "range"
#define DAMAGE_PER_BULLET_KEY "damagePerBullet"
#define PRECISION_KEY "precision"
#define CADENCE_KEY "cadence"
#define SPEED_KEY "speed"
#define BULLETS_PER_SHOT_KEY "bulletsPerShot"

class WeaponInformer {
public:
    virtual ~WeaponInformer() = default;

    virtual double getWeaponInfo(const WeaponType& type, const std::string& info) const = 0;
};

#endif  // WEAPONINFORMER_H
