//
// Created by lionel on 28/05/25.
//

#include "Ak.h"


Ak::Ak(Ak &&other) noexcept : PrimaryWeapon(std::move(other)) {
}

void Ak::attack(Positionable &, const Position &, const Coordinate &) {
}

void Ak::addTo(Inventory &inventory) {
    std::shared_ptr<Weapon> weapon = std::make_shared<Ak>(std::move(*this));
    inventory.add(PRIMARY_INDEX, weapon);
}

WeaponType Ak::getType() {
    return WeaponType::AK47;
}
