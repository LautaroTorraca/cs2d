//
// Created by lionel on 28/05/25.
//

#include "M3.h"
M3::M3(M3 &&other) noexcept : PrimaryWeapon(std::move(other)) {
}

void M3::attack(Positionable &, const Position &, const Coordinate &) {
}

void M3::addTo(Inventory &inventory) {
    std::shared_ptr<Weapon> weapon = std::make_shared<M3>(std::move(*this));
    inventory.add(PRIMARY_INDEX, weapon);
}

WeaponType M3::getType() {
    return WeaponType::M3;
}
