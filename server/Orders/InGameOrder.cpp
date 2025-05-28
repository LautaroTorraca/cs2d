#include "InGameOrder.h"
#include <stdexcept>
#include "ProtocolDefaults.h"
#include "ProtocolContants.h"

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId)
    : InGameOrder(code, playerId, DEFAULT_DIRECTION ,DEFAULT_AMMO, DEFAULT_WEAPON_INFORMATION) {}

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId ,const uint16_t& direction)
    : InGameOrder(code, playerId, direction ,DEFAULT_AMMO, DEFAULT_WEAPON_INFORMATION) {}

InGameOrder::InGameOrder(const uint8_t &code, const size_t &playerId, const uint8_t &weaponInformation)
    : InGameOrder(code, playerId, DEFAULT_DIRECTION ,DEFAULT_AMMO, weaponInformation) {}

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& ammoAmount, const uint8_t& weaponInformation)
    : InGameOrder(code, playerId, DEFAULT_DIRECTION ,ammoAmount, weaponInformation) {}


InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& direction, const uint16_t& ammoAmount, const uint8_t& weaponInformation)
    : playerId(playerId), direction(direction), ammoAmount(ammoAmount),  weaponInformation(weaponInformation) {
    orderTranslator = {
        {ProtocolConstants::PLAYER_MOVEMENT, IN_GAME_MOVE},
        {ProtocolConstants::SHOOT, IN_GAME_SHOOT},
        {ProtocolConstants::PICK_UP_ITEM, IN_GAME_PICK_UP_ITEM},
        {ProtocolConstants::DROP_ITEM, IN_GAME_DROP_ITEM},
        {ProtocolConstants::BUY_AMMO, IN_GAME_BUY_AMMO},
        {ProtocolConstants::BUY_WEAPON, IN_GAME_BUY_WEAPON},
        {ProtocolConstants::SWITCH_WEAPON, IN_GAME_SWITCH_WEAPON},
        {ProtocolConstants::PLANT_BOMB, IN_GAME_PLANT_BOMB},
        {ProtocolConstants::DEFUSE_BOMB, IN_GAME_DEFUSE_BOMB},
        {ProtocolConstants::EXIT_GAME, IN_GAME_EXIT}
    };

    orderType = DO_NOTHING;
    if (orderTranslator.contains(code)) {
        orderType = orderTranslator.at(code);
    }
}

InGameOrder::InGameOrder(InGameOrder&& other) noexcept
    : orderType(other.orderType),
      playerId(other.playerId),
      direction(other.direction),
      ammoAmount(other.ammoAmount),
      weaponInformation(other.weaponInformation),
      orderTranslator(std::move(other.orderTranslator))
{
    other.orderType = DO_NOTHING;
    other.playerId = DEFAULT_PLAYER_ID;
    other.direction = DEFAULT_DIRECTION;
    other.ammoAmount = DEFAULT_AMMO;
    other.weaponInformation = DEFAULT_WEAPON_INFORMATION;
}

InGameOrder& InGameOrder::operator=(InGameOrder&& other) noexcept {
    if (this != &other) {
        orderType = other.orderType;
        playerId = other.playerId;
        direction = other.direction;
        ammoAmount = other.ammoAmount;
        weaponInformation = other.weaponInformation;
        orderTranslator = std::move(other.orderTranslator);

        other.orderType = DO_NOTHING;
        other.playerId = DEFAULT_PLAYER_ID;
        other.direction = DEFAULT_DIRECTION;
        other.ammoAmount = DEFAULT_AMMO;
        other.weaponInformation = DEFAULT_WEAPON_INFORMATION;
    }
    return *this;
}

const OrderType& InGameOrder::getOrderType() const {
    return orderTranslator.at(this->orderType);
}

const size_t& InGameOrder::getPlayerId() const {
    return this->playerId;
}

const uint16_t& InGameOrder::getDirection() const {
    return this->direction;
}

const uint16_t& InGameOrder::getAmmoAmount() const {
    return this->ammoAmount;
}

const uint8_t& InGameOrder::getWeaponInformation() const {
    return this->weaponInformation;
}

