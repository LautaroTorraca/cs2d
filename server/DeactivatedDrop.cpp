//
// Created by lionel on 29/05/25.
//

#include "DeactivatedDrop.h"

DropDTO DeactivatedDrop::getInfo() {
    WeaponInfoDTO weaponInfo = WeaponInfoDTO(0, WeaponType::UNKNOWN);
    return {weaponInfo, Position().getPoint()};
}
