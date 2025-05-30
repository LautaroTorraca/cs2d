//
// Created by lionel on 26/05/25.
//

#include "Player.h"

#include "DeactivatedBacker.h"
#include "ActivatedBacker.h"

Player::Player(const size_t& id, const std::string& name, const GameParser& gameParser, DropPlacer& weaponPlacer): id(id),
name(name),
angle(0),
position(0,0,TILE_SIZE, TILE_SIZE),
healthPoints(INITIAL_LIFE),
backer(std::make_unique<DeactivatedBacker>()), wallet(INITIAL_MONEY),
inventory(gameParser, weaponPlacer, position) {
    this->inventory.set(0, this->weapon);
}

void Player::collision() {
    this->pushBack();
}

void Player::pushBack() {
    this->backer->pushBack(this->position);
    this->backer = std::make_unique<DeactivatedBacker>();

}

void Player::collision(Entity &entity) {
    Damageable& damageable = *this;
    entity.collision(damageable);
}

/*
Player::activateTaker() {
    this->addableTaker = std::make_shared<ActivatedTaker>(this->inventory, this->position);
}

void Player::collision(Addable& addable) {
    this->addableTaker.take(addable); // AddableTaker(ActivedTaker) tiene dentro una referencia a PlayerInventory y manda a dropear la principal(this->inventory.drop()) y a agarrar la nueva(addable.addTo(this->inventory)), inventory pasara a tener una referencia a un AddablePositioner(una interfaz que implementa el GameMap)
    this->addableTaker = std::make_shared<DeactivatedTaker>();
}
*/

void Player::collision(Damager &damager) {
    this->receive(damager);
}

void Player::collision(Damageable & damageable) {
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

void Player::changeAngle(const Coordinate &coordinate) {
    this->angle = this->position.getAngleTo(coordinate);
}

void Player::receive(Damager &damager) {
    damager.damage(this->healthPoints);
}

void Player::buy(Product &product) {
    product.payWith(this->wallet);
    product.addTo(this->inventory);
}

void Player::setWeapon(const uint8_t &index) {
    this->inventory.set(index, this->weapon);
}

void Player::attack(Positionable &positionable, const Coordinate &destination) const {
    this->weapon->attack(positionable, this->position, destination);
}

void Player::takeDrop(DropPlacer &weaponPlacer) {
    weaponPlacer.giveDrops(this->inventory, this->position);
}

PlayerInfoDTO Player::getInfo() {
    std::vector<WeaponInfoDTO> weaponsInfo = this->inventory.getWeaponsInfo();
    WeaponInfoDTO actualWeaponInfo = this->weapon->getInfo();
    CoordinateDTO coordinateInfo = this->position.getPoint();
    PlayerInfoDTO info(this->id, this->name, coordinateInfo, this->angle, this->wallet.getInfo(), this->healthPoints, weaponsInfo, actualWeaponInfo);
    return info;
}
