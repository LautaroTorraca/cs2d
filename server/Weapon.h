//
// Created by lionel on 28/05/25.
//

#ifndef WEAPON_H
#define WEAPON_H
#include "Coordinate.h"
#include "Positionable.h"
#include "WeaponInfoDTO.h"

class Weapon {
    public:
    virtual ~Weapon() = default;
    //Weapon(Weapon&& other) noexcept = default; //TODO: Ver si esto es necesario para llamar al constructor por movimiento de las armas primarias en el metodo add de Inventory
    virtual void attack(Positionable &positionable, const Position &actualPosition, const Coordinate &destination) = 0;
    virtual void recharge(uint16_t& amount) = 0;
    virtual WeaponInfoDTO getInfo() = 0;
};

#endif //WEAPON_H
