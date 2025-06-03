//
// Created by lionel on 03/06/25.
//

#ifndef WEAPONCHANGER_H
#define WEAPONCHANGER_H
#include <cstdint>

struct WeaponChanger {
    const uint8_t weaponSelection;
    WeaponChanger(const uint8_t selection) : weaponSelection(selection) {}
};
#endif //WEAPONCHANGER_H
