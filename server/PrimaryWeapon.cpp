//
// Created by lionel on 28/05/25.
//

#include "PrimaryWeapon.h"


WeaponInfoDTO PrimaryWeapon::getInfo() {
    std::vector<ProjectileDTO> projectilesInfo = this->getProjectilesInfo();
    return {this->ammo, this->getType(), projectilesInfo};
}