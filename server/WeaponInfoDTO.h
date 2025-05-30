//
// Created by lionel on 28/05/25.
//

#ifndef WEAPONINFODTO_H
#define WEAPONINFODTO_H
#include <cstdint>

#include "WeaponConstants.h"


class WeaponInfoDTO {
    uint16_t ammoAmount;
    WeaponType weaponType;
public:
    WeaponInfoDTO(const uint16_t ammoAmount, const WeaponType weaponType) : ammoAmount(ammoAmount), weaponType(weaponType) {}
    WeaponInfoDTO(WeaponInfoDTO&& other) noexcept;
    WeaponInfoDTO& operator=(WeaponInfoDTO&& other) noexcept;
    [[nodiscard]] const uint16_t& getAmmoAmount() const;
    [[nodiscard]] const WeaponType& getWeaponType() const;

};



#endif //WEAPONINFODTO_H
