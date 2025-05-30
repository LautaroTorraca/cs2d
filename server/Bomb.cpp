//
// Created by lionel on 28/05/25.
//

#include "Bomb.h"
#define BOMB_INDEX 3

Bomb::Bomb(Bomb &&) noexcept {
}

void Bomb::attack(Positionable &, const Position &, const Coordinate &) {
}

void Bomb::recharge(uint16_t &) {}

void Bomb::addTo(Inventory &inventory) {
    //TODO: Fijarse si se puede pasar este codigo pseudo-repetido en todas las weapons a la clase padre.
    std::shared_ptr<Weapon> weapon = std::make_shared<Bomb>(std::move(*this));
    inventory.add(BOMB_INDEX, weapon);
}

WeaponInfoDTO Bomb::getInfo() {
    return {1, WeaponType::BOMB};
}
