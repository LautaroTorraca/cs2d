//
// Created by lionel on 26/05/25.
//

#include "Player.h"

#include <iostream>

#include "ActivatedBacker.h"
#include "DeactivatedBacker.h"
#include "NotEnoughMoneyException.h"
#include "WeaponNotFoundException.h"

Player::Player(const size_t& id, const std::string& name, const Skin& skin, const GameParser& gameParser, DropPlacer& weaponPlacer) :
id(id),
name(name),
skin(skin),
parser(gameParser),
angle(0),
healthPoints(parser.getPlayerInfo(INITIAL_LIFE_KEY)),
kills(0),
deaths(0),
backer(std::make_unique<DeactivatedBacker>()),
wallet(parser.getPlayerInfo(INITIAL_MONEY_KEY)),
collectedMoney(0),
status(LIVING),
position(0, 0, parser.getGameMapInfo(TILE_SIZE_KEY), parser.getGameMapInfo(TILE_SIZE_KEY)),
inventory(gameParser, weaponPlacer, position, weapon) {
    this->inventory.set(INITIAL_SELECTED_WEAPON_INDEX);
    std::shared_ptr<Owner> owner(this, [](Owner*) {});
    this->inventory.setOwner(owner);
}

void Player::collision() {
    this->pushBack();
}

void Player::pushBack() {
    this->backer->pushBack(this->position);
    this->backer = std::make_unique<DeactivatedBacker>();

}

void Player::collision(Entity &entity) {
    if (this->status == DEAD) return;
    Damageable& damageable = *this;
    entity.collision(damageable);
}

void Player::collision(Damager &damager) {
    if (this->status == DEAD) return;
    this->receive(damager);
}

void Player::collision(Damageable & damageable) {
    if (this->status == DEAD) return;
    damageable.pushBack();
}

Position Player::displaced(const Coordinate & coordinate) {
    Position displacedPosition = this->position + coordinate;
    return displacedPosition;
}

void Player::allocate(const Position &position)  {
    this->backer = std::make_unique<ActivatedBacker>(this->position);
    this->position.updateLocationTo(position);
}

void Player::changeAngle(const double &angle) {
    this->angle = angle;
}

void Player::die() {
    this->status = DEAD;
    this->deaths++;
    this->inventory.reset();
    this->wallet.wasteAll();
    this->wallet.addMoney(parser.getPlayerInfo(INITIAL_MONEY_KEY));
}

void Player::receive(Damager &damager) {
    damager.damage(this->healthPoints);
    if (this->healthPoints <= 0) {
        this->die();
    }
}

void Player::buy(Product &product) {
    try {
        product.payWith(this->wallet);
        product.addTo(this->inventory);
    } catch (WeaponNotFoundException &) {
        product.reintegrateTo(this->wallet);
    } catch (NotEnoughMoneyException &) {
        //LOGG The player had not enough money.
    }
}

void Player::setWeapon(const uint8_t &index) {
    if (this->status == DEAD) return;
    this->inventory.set(index);
}

void Player::attack(Positionable &positionable) {
    if (this->status == DEAD) return;
    this->weapon->attack(positionable, this->position, this->angle);
}

void Player::takeDrop(DropPlacer &weaponPlacer) {
    if (this->status == DEAD) return;
    weaponPlacer.giveDrops(this->inventory, this->position);
}

void Player::advance(const double &actualTime) {
    this->inventory.advance(actualTime);
}

void Player::reset() {
    Position initialPosition(0,0, parser.getPlayerInfo(TILE_SIZE_KEY), parser.getPlayerInfo(TILE_SIZE_KEY));
    this->position.updateTo(initialPosition);
    this->angle = 0;
    this->status = LIVING;
    this->healthPoints = parser.getPlayerInfo(INITIAL_LIFE_KEY);
    this->backer = std::make_unique<DeactivatedBacker>();
}

void Player::signDeath(std::map<size_t, Player&>& cemetery) {
    if (this->healthPoints == 0) cemetery.emplace(this->id, *this);
}

void Player::removeFrom(Positionable &positionable) {
    if (this->healthPoints != 0) return;
    std::shared_ptr<Entity> entity(this, [](Entity *) {});
    positionable.remove(entity);
}

void Player::release(const uint8_t &index) {
    this->inventory.erase(index);
}

void Player::informKill() {
    this->kills++;
    this->collectedMoney += parser.getPlayerInfo(MONEY_PER_KILL_KEY);
    this->wallet.addMoney(parser.getPlayerInfo(MONEY_PER_KILL_KEY));
}

void Player::noMoreAmmo() {
    this->setWeapon(KNIFE_INDEX);
}

void Player::give(const uint16_t &money) {
    this->collectedMoney += money;
    this->wallet.addMoney(money);
}

void Player::setDeaths(const uint8_t& deaths) { this->deaths = deaths; }

void Player::setKills(const uint8_t& kills) {
    if (this->kills > kills)
        return;
    this->kills = kills;
}

void Player::addCollectedMoney(const uint16_t& collectedMoney) {
    this->collectedMoney += collectedMoney;
}

PlayerInfoDTO Player::getInfo() {
    std::vector<WeaponInfoDTO> weaponsInfo = this->inventory.getWeaponsInfo();
    WeaponInfoDTO actualWeaponInfo = this->weapon->getInfo();
    CoordinateDTO coordinateInfo = this->position.getPoint();
    return {this->id,           this->name,  this->skin,
            coordinateInfo,     this->angle, this->wallet.getInfo(),
            this->healthPoints, weaponsInfo, actualWeaponInfo,
            this->kills, this->deaths, this->status, this->collectedMoney};
}
