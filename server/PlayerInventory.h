//
// Created by lionel on 15/05/25.
//

#ifndef INVENTORY_H
#define INVENTORY_H
#include <map>
#include <memory>

#include "DropPlacer.h"
#include "GameParser.h"
#include "Inventory.h"

#define KNIFE_INDEX 0
#define GLOCK_INDEX 1


class PlayerInventory: public Inventory, public Advancer {
protected:
    std::map<uint8_t, std::shared_ptr<Weapon>> weaponSetter;
    DropPlacer& weaponPlacer;
    Position& position;
    std::shared_ptr<Weapon>& weaponInHands;
    std::vector<uint8_t> bannedObjects;
    std::shared_ptr<Owner> owner;
    std::vector<uint8_t> getKeysCopy();

public:
    std::vector<WeaponInfoDTO> getWeaponsInfo();
    PlayerInventory(const GameParser& gameParser, DropPlacer& weaponPlacer, Position& position,
                    std::shared_ptr<Weapon>& weaponInHands);
    void add(const uint8_t& index, std::shared_ptr<Weapon>& weapon) override;
    void set(const uint8_t& index) override;
    void drop(const uint8_t& index);
    void recharge(const uint8_t& index, uint16_t& ammoAmount) override;
    void addBanned(const uint8_t& index);
    void setOwner(const std::shared_ptr<Owner>& owner);
    void advance(const double& actualTime) override;
    void erase(const uint8_t& index);
    void reset();
    ~PlayerInventory() override = default;
};


#endif  // INVENTORY_H
