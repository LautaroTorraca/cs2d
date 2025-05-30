//
// Created by lionel on 28/05/25.
//

#include "Knife.h"

void Knife::attack(Positionable &, const Position &, const Coordinate &) {

}

void Knife::recharge(uint16_t &) {}

WeaponInfoDTO Knife::getInfo() {
    return {1, WeaponType::KNIFE};
}
