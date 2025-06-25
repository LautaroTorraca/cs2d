//
// Created by lionel on 26/05/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "Constants/Skin.h"
#include "DTO/PlayerInfoDTO.h"
#include "GameLogic/Interfaces/Backer.h"
#include "GameLogic/Interfaces/Entity.h"
#include "GameLogic/Shop/Buyer.h"
#include "GameLogic/Shop/Wallet.h"
#include "GameLogic/Utils/DeactivatedBacker.h"
#include "common/Constants/PlayerStatus.h"

#include "PlayerInventory.h"

#define INITIAL_LIFE_KEY "initialLife"
#define INITIAL_MONEY_KEY "initialMoney"
#define MONEY_PER_KILL_KEY "moneyPerKill"
#define INITIAL_SELECTED_WEAPON_INDEX 0


class Player : public Entity, public Damageable, public Buyer, public Advancer, public Owner {
    size_t id;
    std::string name;
    Skin skin;
    const GameParser& parser;
    std::shared_ptr<Weapon> weapon;
    double angle;
    uint8_t healthPoints;
    uint8_t kills;
    uint8_t deaths;
    std::unique_ptr<Backer> backer;
    Wallet wallet;
    uint16_t collectedMoney;

protected:
    PlayerStatus status;
    Position position;
    PlayerInventory inventory;
public:

    Player(const size_t& id, const std::string& name, const Skin& skin, const GameParser& gameParser, DropPlacer& weaponPlacer);

    ~Player() override = default;

    void collision() override;

    void collision(Entity &other) override;

    void collision(Damager &other) override;

    void collision(Damageable &other) override;

    Position displaced(const Coordinate & coordinate) override;

    void allocate(const Position &position) override;

    void changeAngle(const double &angle);

    void die();

    void receive(Damager &damager) override;

    void buy(Product &product) override;

    virtual void setWeapon(const uint8_t& index);

    void pushBack() override;

    virtual void attack(Positionable & positionable);

    void takeDrop(DropPlacer& weaponPlacer);

    void advance(const double &actualTime) override;

    virtual void reset();

    void signDeath(std::map<size_t, Player &> &cemetery);

    void removeFrom(Positionable &positionable);

    void release(const uint8_t& index) override;

    void informKill() override;

    void noMoreAmmo() override;

    void give(const uint16_t& money);

    PlayerInfoDTO getInfo();

    void setDeaths(const uint8_t& deaths);

    void setKills(const uint8_t& kills);

    void addCollectedMoney(const uint16_t& collectedMoney);
};



#endif //PLAYER_H
