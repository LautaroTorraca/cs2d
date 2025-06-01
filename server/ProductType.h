//
// Created by lionel on 27/05/25.
//

#ifndef PRODUCTIDS_H
#define PRODUCTIDS_H
#include <cstdint>

enum ProductType : std::uint8_t {
    AK_47_WEAPON = 1,
    M3_WEAPON = 2,
    AWP_WEAPON = 3,
    PRIMARY_AMMO = 4,
    SECONDARY_AMMO = 5
};

#endif //PRODUCTIDS_H
