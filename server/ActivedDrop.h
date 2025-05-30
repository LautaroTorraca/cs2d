//
// Created by lionel on 29/05/25.
//

#ifndef ACTIVEDROP_H
#define ACTIVEDROP_H
#include <cstdint>
#include <memory>

#include "Drop.h"
#include "Inventory.h"
#include "Weapon.h"


class ActivedDrop : public Drop {
    uint8_t index;
    std::shared_ptr<Weapon> droppedWeapon;
    Position position;
public:
    ActivedDrop(const uint8_t& index, const std::shared_ptr<Weapon>& weapon, const Position& position) : index(index), droppedWeapon(weapon) {
        this->position.updateTo(position);

    }
    void giveTo(Inventory &inventory) override;
    DropDTO getInfo() override;
    ~ActivedDrop() override = default;
};



#endif //ACTIVEDROP_H
