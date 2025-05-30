//
// Created by lionel on 15/05/25.
//

#ifndef INVENTORY_H
#define INVENTORY_H
#include <map>
#include <memory>

#include "GameParser.h"
#include "Inventory.h"
#include "DropPlacer.h"

#define KNIFE_INDEX 0
#define GLOCK_INDEX 1


class PlayerInventory : public Inventory {
protected:
    std::map<uint8_t, std::shared_ptr<Weapon>> weaponSetter;
    DropPlacer& weaponPlacer;
    Position& position;
public:
    std::vector<WeaponInfoDTO> getWeaponsInfo();

    PlayerInventory(const GameParser& gameParser, DropPlacer& weaponPlacer, Position& position);
    void add(const uint8_t &index, std::shared_ptr<Weapon> &weapon) override;
    void set(const uint8_t &index, std::shared_ptr<Weapon> &actualWeapon) override;
    void drop(const uint8_t& index);
    void recharge(const uint8_t &index, uint16_t &ammoAmount) override;
    ~PlayerInventory() override = default;
};



#endif //INVENTORY_H
