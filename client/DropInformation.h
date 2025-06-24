//
// Created by lionel on 03/06/25.
//

#ifndef DROPINFORMATION_H
#define DROPINFORMATION_H
#include "CoordinateInformation.h"
#include "WeaponInformation.h"

struct DropInformation {
    const WeaponInformation weapon;
    const CoordinateInformation position;
    DropInformation(const WeaponInformation& weaponInfo, const CoordinateInformation& positionInfo):
            weapon(weaponInfo), position(positionInfo) {}
};

#endif  // DROPINFORMATION_H
