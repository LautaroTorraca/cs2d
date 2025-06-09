//
// Created by lionel on 03/06/25.
//

#ifndef WEAPONINFORMATION_H
#define WEAPONINFORMATION_H
#include <cstdint>
#include <vector>

#include "server/WeaponConstants.h"

#include "ProjectileInformation.h"

struct WeaponInformation {
    WeaponType weaponType;
    uint16_t ammoAmount;
    std::vector<ProjectileInformation> projectilesInfo;
    WeaponInformation(const WeaponType& type, const uint16_t& ammoAmount,
                      const std::vector<ProjectileInformation>& projectilesInfo):
            weaponType(type), ammoAmount(ammoAmount), projectilesInfo(projectilesInfo) {}
};

#endif  // WEAPONINFORMATION_H
