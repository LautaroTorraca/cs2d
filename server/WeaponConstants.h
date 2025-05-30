//
// Created by lionel on 27/05/25.
//

#ifndef WEAPONCONSTANTS_H
#define WEAPONCONSTANTS_H

#pragma once

#include <cstdint>

enum class WeaponType : uint8_t {
    KNIFE = 0x00,
    GLOCK = 0x01,
    AK47 = 0x02,
    M3 = 0x03,
    AWP = 0x04,
    BOMB = 0x05,
    UNKNOWN = 0xFF
};

#endif //WEAPONCONSTANTS_H
