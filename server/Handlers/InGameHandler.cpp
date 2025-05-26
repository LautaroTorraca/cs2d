#include "InGameHandler.h"

#include <stdexcept>

#include "Constants/OpCodesConstans.h"
#include "Constants/KeyContants.h"

InGameHandler::InGameHandler(Socket& user, const size_t &userId) : userSocket(user), userId(userId), reader(user) {
    requestMapper[OPCODE_PLAYER_MOVEMENT] = [&]() { return moveRequest(); };
    requestMapper[OPCODE_SHOOT] = [&]() { return shootRequest(); };
    requestMapper[OPCODE_BUY_AMMO] = [&]() { return buyAmmoRequest(); };
    requestMapper[OPCODE_BUY_WEAPON] = [&]() { return buyWeaponsRequest(); };
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
    const uint8_t direction = reader.u8tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_PLAYER_MOVEMENT));
    message.emplace(directionKey, std::vector<char>(SINGLE_VALUE, direction));

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

Request InGameHandler::buyAmmoRequest() const {
    const uint8_t amount = reader.u8tReader();
    const uint8_t weapon = reader.u8tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_BUY_AMMO));
    message.emplace(ammoAmountKey, std::vector<char>(SINGLE_VALUE, amount));
    message.emplace(weaponKey, std::vector<char>(SINGLE_VALUE, weapon));

    return Request(userId, message);
}

Request InGameHandler::buyWeaponsRequest() const {
    const uint8_t weapon = reader.u8tReader();
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_BUY_WEAPON));
    message.emplace(weaponKey, std::vector<char>(SINGLE_VALUE, weapon));

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
