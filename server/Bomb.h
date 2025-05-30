//
// Created by lionel on 28/05/25.
//

#ifndef BOMB_H
#define BOMB_H
#include "Addable.h"
#include "Weapon.h"


class Bomb : public Weapon, public Addable {
public:
    ~Bomb() override = default;
    Bomb(Bomb&& other) noexcept;
    void attack(Positionable &positionable, const Position &actualPosition, const Coordinate &destination) override;
    void recharge(uint16_t &amount) override;
    void addTo(Inventory &inventory) override;
    WeaponInfoDTO getInfo() override;
};



#endif //BOMB_H
