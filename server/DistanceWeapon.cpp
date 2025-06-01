//
// Created by lionel on 01/06/25.
//

#include "DistanceWeapon.h"

DistanceWeapon::DistanceWeapon(DistanceWeapon &&other) noexcept : actualTime(other.actualTime), projectiles(std::move(other.projectiles)) {
    if (this != &other) {
        other.actualTime = 0;
        other.projectiles = std::vector<std::shared_ptr<Projectile>>();
    }
}

std::vector<std::shared_ptr<Projectile>> DistanceWeapon::getProjectilesCopy() {
    std::vector<std::shared_ptr<Projectile>> projectilesCopy;
    for (auto& projectile : this->projectiles) {
        projectilesCopy.emplace_back(projectile);
    }
    return projectilesCopy;
}

std::vector<ProjectileDTO> DistanceWeapon::getProjectilesInfo() const {
    std::vector<ProjectileDTO> projectilesInfo;
    for (auto& projectile : this->projectiles) {
        projectilesInfo.emplace_back(projectile->getInfo());
    }
    return projectilesInfo;
}

void DistanceWeapon::advance(const double &actualTime) {
    this->actualTime = actualTime;
    std::vector<std::shared_ptr<Projectile>> projectilesCopy = this->getProjectilesCopy();
    for (auto &projectile : projectilesCopy) {
        projectile->advance(actualTime);
        projectile->erase(this->projectiles, this->owner);
    }
}
