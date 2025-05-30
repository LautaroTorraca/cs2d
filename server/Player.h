//
// Created by lionel on 26/05/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "Backer.h"
#include "Buyer.h"
#include "DeactivatedBacker.h"
#include "Entity.h"
#include "PlayerInfoDTO.h"
#include "PlayerInventory.h"
#include "Wallet.h"

#define TILE_SIZE 32
#define INITIAL_LIFE 100
#define INITIAL_MONEY 500


class Player : public Entity, public Damageable, public Buyer {
    size_t id;
    std::string name;
    double angle;
    Position position;
    uint8_t healthPoints;
    std::unique_ptr<Backer> backer;
    Wallet wallet;
    PlayerInventory inventory;
    std::shared_ptr<Weapon> weapon;

public:

    Player(const size_t& id, const std::string& name, const GameParser& gameParser, DropPlacer& weaponPlacer);

    ~Player() override = default;

    void collision() override;

    void collision(Entity &other) override;

    void collision(Damager &other) override;

    void collision(Damageable &other) override;

    Position displaced(const Coordinate & coordinate) override;

    void allocate(const Position &position) override;

    void changeAngle(const Coordinate &coordinate);

    void receive(Damager &damager) override;

    void buy(Product &product) override;

    void setWeapon(const uint8_t& index);

    void pushBack() override;

    void attack(Positionable & positionable, const Coordinate & destination) const;

    void takeDrop(DropPlacer& weaponPlacer);

    PlayerInfoDTO getInfo();
};



#endif //PLAYER_H
