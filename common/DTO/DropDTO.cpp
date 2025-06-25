//
// Created by lionel on 29/05/25.
//

#include "DropDTO.h"

DropDTO::DropDTO(DropDTO&& drop) noexcept : weapon(std::move(drop.weapon)), position(drop.position) {
    drop.weapon = WeaponInfoDTO(0, WeaponType::UNKNOWN);
    drop.position = CoordinateDTO(0, 0);
}

const WeaponInfoDTO & DropDTO::getDropInfo() const {
    return this->weapon;
}

const CoordinateDTO & DropDTO::getPosition() const {
    return this->position;
}
