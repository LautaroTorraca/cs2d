//
// Created by lionel on 29/05/25.
//

#include "DropDTO.h"

DropDTO::DropDTO(DropDTO&& drop) noexcept: weapon(std::move(drop.weapon)), position(drop.position) {
    // TODO: Implementar como debe quedar el estado inconsistente del otro.
}

const WeaponInfoDTO& DropDTO::getDropInfo() const { return this->weapon; }

const CoordinateDTO& DropDTO::getPosition() const { return this->position; }
