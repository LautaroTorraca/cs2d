//
// Created by lionel on 03/06/25.
//

#ifndef PROJECTILEINFORMATION_H
#define PROJECTILEINFORMATION_H
#include "CoordinateInformation.h"

struct ProjectileInformation {
    CoordinateInformation projectilePosition;
    explicit ProjectileInformation(const CoordinateInformation& projectilePosition):
            projectilePosition(projectilePosition) {}
};

#endif  // PROJECTILEINFORMATION_H
