//
// Created by lionel on 28/05/25.
//

#include "Awp.h"

Awp::Awp(Awp &&other) noexcept : PrimaryWeapon(std::move(other)) {
}

void Awp::attack(Positionable &, const Position &, const Coordinate &) {

}

void Awp::addTo(Inventory &inventory) {
    std::shared_ptr<Weapon> weapon = std::make_shared<Awp>(std::move(*this));
    inventory.add(PRIMARY_INDEX, weapon);
}

WeaponType Awp::getType() {
    return WeaponType::AWP;
}
