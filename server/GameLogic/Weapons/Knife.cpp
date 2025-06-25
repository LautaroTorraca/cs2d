//
// Created by lionel on 28/05/25.
//

#include "Knife.h"

#include <cmath>

#include "GameLogic/Utils/Randomizator.h"

#include "DirectProjectile.h"

void Knife::attack(Positionable &positionable, const Position &actualPosition, const double &angle) {
    double radianAngle = ((angle + ANGLE_BIAS)*M_PI/PI_TO_GRADES);
    Coordinate direction(std::cos(radianAngle), std::sin(radianAngle));
    Randomizator randomizer;
    double damage = randomizer.getRandom(this->knifeMinDamage, this->knifeMaxDamage);
    this->projectiles.emplace_back(std::make_shared<DirectProjectile>(positionable, actualPosition, direction, knifeRange, 1, knifeSpeed, damage));
}

WeaponInfoDTO Knife::getInfo() {
    std::vector<ProjectileDTO> stabbingsInfo = this->getProjectilesInfo();
    return { WeaponType::KNIFE, stabbingsInfo};
}
