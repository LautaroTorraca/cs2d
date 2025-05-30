//
// Created by lionel on 29/05/25.
//

#include "ActivedDrop.h"

void ActivedDrop::giveTo(Inventory &inventory) {
    inventory.add(this->index, this->droppedWeapon);
}

DropDTO ActivedDrop::getInfo() {
    WeaponInfoDTO weaponInfo = this->droppedWeapon->getInfo();
    return {weaponInfo, this->position.getPoint()};
}
