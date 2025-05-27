#ifndef WEAPON_CONSTANTS_H
#define WEAPON_CONSTANTS_H

#include <cstdint>

namespace WeaponConstants {
    // IDs de Armas
    enum WeaponId : uint8_t {
        KNIFE = 0x00,
        GLOCK = 0x01,
        AK47 = 0x02,
        M3 = 0x03,
        AWP = 0x04,
        BOMB = 0x05
    };

}

#endif // WEAPON_CONSTANTS_H
