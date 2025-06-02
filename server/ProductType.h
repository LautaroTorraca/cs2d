//
// Created by lionel on 27/05/25.
//

#ifndef PRODUCTIDS_H
#define PRODUCTIDS_H
#include <cstdint>

enum ProductType : std::uint8_t {
    AK_47_WEAPON = 0X01,
    M3_WEAPON = 0X02,
    AWP_WEAPON = 0X03,
    PRIMARY_AMMO = 0X04,
    SECONDARY_AMMO = 0X05,
    NONE = 0xFF
};

#endif //PRODUCTIDS_H
