#pragma once

#include <cstdint>
#include "PlayerDataConstants.h"

enum class WeaponId : uint8_t {
    KNIFE = 0x00,
    GLOCK = 0x01,
    AK47 = 0x02,
    M3 = 0x03,
    AWP = 0x04,
    BOMB = 0x05
};
