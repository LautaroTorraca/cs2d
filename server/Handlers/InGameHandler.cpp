#include "InGameHandler.h"

#include <cstring>
#include <stdexcept>

#include "Constants/OpCodesConstans.h"
#include "Constants/KeyContants.h"

InGameHandler::InGameHandler(Socket& user, const size_t &userId) : userSocket(user), userId(userId), reader(user) {
    requestMapper[OPCODE_PLAYER_MOVEMENT] = [&]() { return moveRequest(); };
    requestMapper[OPCODE_SHOOT] = [&]() { return shootRequest(); };
    requestMapper[OPCODE_BUY] = [&]() { return buyRequest(); };
    //requestMapper[OPCODE_BUY_WEAPON] = [&]() { return buyWeaponsRequest(); };
    requestMapper[OPCODE_PICK_UP_ITEM] = [&]() { return pickUpItemRequest(); };
    requestMapper[OPCODE_DROP_ITEM] = [&]() { return dropItemRequest(); };
    requestMapper[OPCODE_SWITCH_WEAPON] = [&]() { return switchWeaponsRequest(); };
    requestMapper[OPCODE_PLANT_BOMB] = [&]() { return plantBombRequest(); };
    requestMapper[OPCODE_DEFUSE_BOMB] = [&]() { return defuseBombRequest(); };
    requestMapper[OPCODE_EXIT_GAME] = [&]() { return exitGameRequest(); };
}

Request InGameHandler::handle(const uint8_t opcode) const {
    if (!requestMapper.contains(opcode)) {
        throw std::runtime_error("Opcode de InGame no registrado: " + std::to_string(opcode));
    }
    return requestMapper.at(opcode)();
}

Request InGameHandler::moveRequest() const {
    const uint16_t direction = reader.u16tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_PLAYER_MOVEMENT));
    std::vector<char> serializedDirection(sizeof(uint16_t));
    std::memcpy(serializedDirection.data(), &direction, sizeof(uint16_t));
    message.emplace(directionKey, serializedDirection);
    return Request(userId, message);
}

// TODO REVISAR DE ACA
// PENSAR EN ALGUN FORMA DE ENCAPSULAR LOGICA REPETIDA (no ahora jeje)
Request InGameHandler::shootRequest() const {
    const uint8_t direction = reader.u8tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_SHOOT));
    message.emplace(directionKey, std::vector<char>(SINGLE_VALUE, direction));

    return Request(userId, message);
}

Request InGameHandler::pickUpItemRequest() const {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_PICK_UP_ITEM));

    return Request(userId, message);
}

Request InGameHandler::dropItemRequest() const {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_DROP_ITEM));

    return Request(userId, message);
}

Request InGameHandler::buyRequest() const {
    const uint8_t weapon = reader.u8tReader();
    const uint8_t amount = reader.u8tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_BUY));
    message.emplace(weaponKey, std::vector<char>(SINGLE_VALUE, weapon));
    message.emplace(ammoAmountKey, std::vector<char>(SINGLE_VALUE, amount));

    return Request(userId, message);
}


Request InGameHandler::changeAngleRequest() const {
    const double x = reader.doubleRead();
    const double y = reader.doubleRead();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_CHANGE_ANGLE));
    std::vector<char> xValue(sizeof(double));
    std::memcpy(xValue.data(), &x, sizeof(double));
    message.emplace(xPosKey, xValue);
    std::vector<char> yValue(sizeof(double));
    std::memcpy(yValue.data(), &y, sizeof(double));
    message.emplace(yPosKey, xValue);

    return Request(userId, message);
}

Request InGameHandler::switchWeaponsRequest() const {
    const uint8_t slot = reader.u8tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_SWITCH_WEAPON));
    message.emplace(slotKey, std::vector<char>(SINGLE_VALUE, slot));

    return Request(userId, message);
}

Request InGameHandler::plantBombRequest() const {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_PLANT_BOMB));

    return Request(userId, message);
}

Request InGameHandler::defuseBombRequest() const {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_DEFUSE_BOMB));

    return Request(userId, message);
}

Request InGameHandler::exitGameRequest() const {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_EXIT_GAME));

    return Request(userId, message);
}

InGameHandler::~InGameHandler() = default;
