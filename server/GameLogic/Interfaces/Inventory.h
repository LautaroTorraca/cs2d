#pragma once
#include <memory>

#include "server/GameLogic/Weapons/Weapon.h"

class Inventory {
    public:
    virtual ~Inventory() = default;

    virtual void add(const uint8_t &index, std::shared_ptr<Weapon> &weapon) = 0;
    virtual void set(const uint8_t &index) = 0;
    virtual void recharge(const uint8_t& index, uint16_t& ammoAmount) = 0;
};
