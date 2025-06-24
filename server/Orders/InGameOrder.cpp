#include "InGameOrder.h"
#include <stdexcept>

#include "server/Constants/MovementConstants.h"
#include "server/Constants/ProtocolDefaults.h"
#include "server/Constants/ProtocolContants.h"

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId) : InGameOrder(code, playerId, DEFAULT_DIRECTION, DEFAULT_ANGLE ,DEFAULT_AMMO, DEFAULT_WEAPON_INFORMATION, {0, 0}) {}

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId, const std::pair<double, double>& position) : InGameOrder(code, playerId, DEFAULT_DIRECTION, DEFAULT_ANGLE, DEFAULT_AMMO, DEFAULT_WEAPON_INFORMATION, position) {}

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId ,const uint16_t& direction)
    : InGameOrder(code, playerId, direction, DEFAULT_ANGLE, DEFAULT_AMMO, DEFAULT_WEAPON_INFORMATION, {0, 0}) {}

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId, const double& angle)
    : InGameOrder(code, playerId, DEFAULT_DIRECTION, angle, DEFAULT_AMMO, DEFAULT_WEAPON_INFORMATION, {0, 0}) {}

InGameOrder::InGameOrder(const uint8_t &code, const size_t &playerId, const uint8_t &weaponInformation)
    : InGameOrder(code, playerId, DEFAULT_DIRECTION, DEFAULT_ANGLE,DEFAULT_AMMO, weaponInformation, {0, 0}) {}

InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& amount, const uint8_t& weaponInformation)
    : InGameOrder(code, playerId, DEFAULT_DIRECTION, DEFAULT_ANGLE, amount, weaponInformation, {0, 0}) {}


InGameOrder::InGameOrder(const uint8_t& code, const size_t& playerId, const uint16_t& direction, const double& angle, const uint16_t& amount, const uint8_t& weaponInformation, const std::pair<double, double>& position)
    : playerId(playerId), direction(direction), angle(angle), amount(amount),  weaponInformation(weaponInformation), position(position) {
    orderTranslator = {
        {ProtocolConstants::PLAYER_MOVEMENT, IN_GAME_MOVE},
        {ProtocolConstants::ATTACK, IN_GAME_SHOOT},
        {ProtocolConstants::PICK_UP_ITEM, IN_GAME_PICK_UP_ITEM},
        {ProtocolConstants::DROP_ITEM, IN_GAME_DROP_ITEM},
        {ProtocolConstants::BUY, IN_GAME_BUY},
        {ProtocolConstants::CHANGE_ANGLE, IN_GAME_CHANGE_ANGLE},
        {ProtocolConstants::SWITCH_WEAPON, IN_GAME_SWITCH_WEAPON},
        {ProtocolConstants::PLANT_BOMB, IN_GAME_PLANT_BOMB},
        {ProtocolConstants::DEFUSE_BOMB, IN_GAME_DEFUSE_BOMB},
        {ProtocolConstants::EXIT_GAME, IN_GAME_EXIT}
    };

    toProduct = {
        {AK_47_WEAPON, AK_47_WEAPON},
        {M3_WEAPON, M3_WEAPON},
        { AWP_WEAPON, AWP_WEAPON },
        {PRIMARY_AMMO, PRIMARY_AMMO},
        {SECONDARY_AMMO, SECONDARY_AMMO}
    };

    if (!this->toProduct.contains(weaponInformation)) {
        toProduct.emplace(weaponInformation, ProductType::NONE);
    }

    movementTranslator = {
        {UP_MOVEMENT, Movement::UP},
        {RIGHT_MOVEMENT, Movement::RIGHT},
        {DOWN_MOVEMENT, Movement::DOWN},
        {LEFT_MOVEMENT, Movement::LEFT}
    };

    if (!movementTranslator.contains(direction)) {
        movementTranslator.emplace(direction, Movement::STAND);
    }

    orderType = DO_NOTHING;
    if (orderTranslator.contains(code)) {
        orderType = orderTranslator.at(code);
    }
}

InGameOrder::InGameOrder(InGameOrder&& other) noexcept
    : orderType(other.orderType),
    playerId(other.playerId),
    direction(other.direction),
    angle(other.angle),
    amount(other.amount),
    weaponInformation(other.weaponInformation),
    orderTranslator(std::move(other.orderTranslator)),
    movementTranslator(std::move(other.movementTranslator)),
    toProduct(std::move(other.toProduct)),
    position(std::move(other.position))
{
    other.orderType = DO_NOTHING;
    other.playerId = DEFAULT_PLAYER_ID;
    other.direction = DEFAULT_DIRECTION;
    other.angle = DEFAULT_ANGLE;
    other.amount = DEFAULT_AMMO;
    other.weaponInformation = DEFAULT_WEAPON_INFORMATION;
    other.movementTranslator = std::map<uint16_t, Movement>();
    other.toProduct = std::map<uint8_t, ProductType>();
    other.position = std::pair<double, double>();
}

InGameOrder& InGameOrder::operator=(InGameOrder&& other) noexcept {
    if (this != &other) {
        orderType = other.orderType;
        playerId = other.playerId;
        direction = other.direction;
        angle = other.angle;
        amount = other.amount;
        weaponInformation = other.weaponInformation;
        orderTranslator = std::move(other.orderTranslator);
        movementTranslator = std::move(other.movementTranslator);
        toProduct = std::move(other.toProduct);
        position = std::move(other.position);

        other.orderType = DO_NOTHING;
        other.playerId = DEFAULT_PLAYER_ID;
        other.direction = DEFAULT_DIRECTION;
        other.angle = DEFAULT_ANGLE;
        other.amount = DEFAULT_AMMO;
        other.weaponInformation = DEFAULT_WEAPON_INFORMATION;
        other.movementTranslator = std::map<uint16_t, Movement>();
        other.toProduct = std::map<uint8_t, ProductType>();
        other.position = std::pair<double, double>();
    }
    return *this;
}

const OrderType& InGameOrder::getOrderType() const {
    return orderTranslator.at(this->orderType);
}

const size_t& InGameOrder::getPlayerId() const {
    return this->playerId;
}

const Movement& InGameOrder::getDirection() const {
    return this->movementTranslator.at(this->direction);
}

const uint16_t& InGameOrder::getAmount() const {
    return this->amount;
}

const uint8_t& InGameOrder::getWeaponInformation() const {
    return this->weaponInformation;
}

const ProductType & InGameOrder::getProduct() const {
    return this->toProduct.at(this->weaponInformation);
}

const std::pair<double, double>& InGameOrder::getPosition() const { return this->position; }

const double& InGameOrder::getAngle() const { return this->angle; }
