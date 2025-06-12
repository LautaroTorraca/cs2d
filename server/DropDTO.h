//
// Created by lionel on 29/05/25.
//

#ifndef DROPDTO_H
#define DROPDTO_H
#include <algorithm>

#include "CoordinateDTO.h"
#include "WeaponInfoDTO.h"


class DropDTO {
    WeaponInfoDTO weapon;
    CoordinateDTO position;

public:
    DropDTO(WeaponInfoDTO& weapon, const CoordinateDTO& position):
            weapon(std::move(weapon)), position(position) {}
    DropDTO(DropDTO&& drop) noexcept;
    [[nodiscard]] const WeaponInfoDTO& getDropInfo() const;
    [[nodiscard]] const CoordinateDTO& getPosition() const;
};


#endif  // DROPDTO_H
