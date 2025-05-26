#include "InGameProtocol.h"

#include "KeyContants.h"
#include "Constants/protocolContants.h"
#include "Constants/ProtocolDefaults.h"

InGameProtocol::InGameProtocol(std::map<size_t, std::unique_ptr<Socket>>& connectedUsers)
    : connectedUsers(connectedUsers)
{
    using namespace ProtocolConstants;

    requestHandlers[PLAYER_MOVEMENT] = [this](const Request& request) { return movementHandler(request); };
    requestHandlers[SHOOT] = [this](const Request& request) { return shootHandler(request); };
    requestHandlers[PICK_UP_ITEM] = [this](const Request& request) { return pickUpItemHandler(request); };
    requestHandlers[DROP_ITEM] = [this](const Request& request) { return dropItemHandler(request); };
    requestHandlers[BUY_AMMO] = [this](const Request& request) { return buyAmmoHandler(request); };
    requestHandlers[BUY_WEAPON] = [this](const Request& request) { return buyWeaponHandler(request); };
    requestHandlers[SWITCH_WEAPON] = [this](const Request& request) { return switchWeaponHandler(request); };
    requestHandlers[PLANT_BOMB] = [this](const Request& request) { return plantBombHandler(request); };
    requestHandlers[DEFUSE_BOMB] = [this](const Request& request) { return defuseBombHandler(request); };
    requestHandlers[EXIT_GAME] = [this](const Request& request) { return exitHandler(request); };
}


InGameOrder InGameProtocol::handleRequest(const Request& request) {
    const uint8_t opCode = request.getRequest().at(opCodeKey).front();

    if (!requestHandlers.contains(opCode)) {
        throw -1; //TODO FIX
    }
    return requestHandlers[opCode](request);
}
InGameOrder InGameProtocol::movementHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const uint8_t direction = message.at(directionKey).front();

    return InGameOrder(ProtocolConstants::PLAYER_MOVEMENT, clientId, direction);
}

InGameOrder InGameProtocol::shootHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const uint8_t direction = message.at(directionKey).front();

    return InGameOrder(ProtocolConstants::SHOOT, clientId, direction);
}

InGameOrder InGameProtocol::pickUpItemHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    return InGameOrder(ProtocolConstants::PICK_UP_ITEM, clientId);
}

InGameOrder InGameProtocol::dropItemHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    return InGameOrder(ProtocolConstants::DROP_ITEM, clientId);
}

InGameOrder InGameProtocol::switchWeaponHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const uint8_t slot = message.at(weaponKey).front();

    return InGameOrder(ProtocolConstants::SWITCH_WEAPON, clientId, slot);  //weapon, direction, ammout dummys
}

InGameOrder InGameProtocol::buyWeaponHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const uint8_t weapon = message.at(weaponKey).front();

    return InGameOrder(ProtocolConstants::BUY_WEAPON, clientId, weapon); //slot, direction, ammout dummys
}

InGameOrder InGameProtocol::buyAmmoHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const uint8_t ammoAmount = message.at(ammoAmountKey).front();
    const uint8_t weapon = message.at(weaponKey).front();

    return InGameOrder(ProtocolConstants::BUY_AMMO, clientId, ammoAmount, weapon);
}


InGameOrder InGameProtocol::plantBombHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    return InGameOrder(ProtocolConstants::PLANT_BOMB, clientId);
}

InGameOrder InGameProtocol::defuseBombHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    return InGameOrder(ProtocolConstants::DEFUSE_BOMB, clientId);
}


InGameOrder InGameProtocol::exitHandler(const Request& request) {
    const size_t clientId = request.getId();

    return InGameOrder(ProtocolConstants::EXIT_GAME, clientId);
}


//NO LA USAMOS NUNCA, REVISAR CUANDO ME LOS TENGO QUE GUARDAR
void InGameProtocol::registerClient(size_t clientId, std::unique_ptr<InGameHandler> handler) {
    usersInGame.emplace(clientId, std::move(handler));
}

void InGameProtocol::end() {
    usersInGame.clear();
}
