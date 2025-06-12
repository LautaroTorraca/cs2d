//
// Created by lionel on 28/05/25.
//

#ifndef WEAPONINFODTO_H
#define WEAPONINFODTO_H
#include <cstdint>
#include <utility>
#include <vector>

#include "ProjectileDTO.h"
#include "WeaponConstants.h"


class WeaponInfoDTO {
    uint16_t ammoAmount;
    WeaponType weaponType;
    std::vector<ProjectileDTO> projectilesInfo;

public:
    WeaponInfoDTO(const uint16_t ammoAmount, const WeaponType weaponType,
                  std::vector<ProjectileDTO>& projectilesInfo):
            ammoAmount(ammoAmount),
            weaponType(weaponType),
            projectilesInfo(std::move(projectilesInfo)) {}
    WeaponInfoDTO(const WeaponType weaponType, std::vector<ProjectileDTO>& projectilesInfo):
            ammoAmount(0), weaponType(weaponType), projectilesInfo(std::move(projectilesInfo)) {}
    WeaponInfoDTO(const uint16_t ammoAmount, const WeaponType weaponType):
            ammoAmount(ammoAmount), weaponType(weaponType) {}
    WeaponInfoDTO(WeaponInfoDTO&& other) noexcept;
    WeaponInfoDTO& operator=(WeaponInfoDTO&& other) noexcept;
    [[nodiscard]] const uint16_t& getAmmoAmount() const;
    [[nodiscard]] const WeaponType& getWeaponType() const;
    [[nodiscard]] const std::vector<ProjectileDTO>& getProjectilesInfo() const;
};


#endif  // WEAPONINFODTO_H
