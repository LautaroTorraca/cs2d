//
// Created by lionel on 28/05/25.
//

#include "WeaponInfoDTO.h"

WeaponInfoDTO::WeaponInfoDTO(WeaponInfoDTO &&other) noexcept : ammoAmount(other.ammoAmount), weaponType(other.weaponType) {
    if (this != &other) {
        other.ammoAmount = 0;
        other.weaponType = WeaponType::UNKNOWN;
    }
}

WeaponInfoDTO & WeaponInfoDTO::operator=(WeaponInfoDTO &&other) noexcept {
    if (this != &other) {
        this->ammoAmount = other.ammoAmount;
        this->weaponType = other.weaponType;
        other.ammoAmount = 0;
        other.weaponType = WeaponType::UNKNOWN;
    }
    return *this;
}

const uint16_t& WeaponInfoDTO::getAmmoAmount() const {
    return this->ammoAmount;
}

const WeaponType& WeaponInfoDTO::getWeaponType() const {
    return this->weaponType;
}

const std::vector<ProjectileDTO> & WeaponInfoDTO::getProjectilesInfo() const {
    return this->projectilesInfo;
}