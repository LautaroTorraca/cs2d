//
// Created by lionel on 28/05/25.
//

#include "Knife.h"
#include <cmath>

#include "DirectProjectile.h"
#include "Randomizator.h"

void Knife::attack(Positionable &positionable, const Position &actualPosition, const double &angle) {
    Coordinate direction(std::cos(angle), -std::sin(angle));
    Randomizator randomizer;
    double damage = randomizer.getRandom(this->knifeMinDamage, this->knifeMaxDamage);
    this->projectiles.emplace_back(std::make_shared<DirectProjectile>(positionable, actualPosition, direction, knifeRange, 1, knifeSpeed, damage));
}

WeaponInfoDTO Knife::getInfo() {
    std::vector<ProjectileDTO> stabbingsInfo = this->getProjectilesInfo();
    return { WeaponType::KNIFE, stabbingsInfo};
}
