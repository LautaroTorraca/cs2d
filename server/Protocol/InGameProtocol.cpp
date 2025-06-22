#include "InGameProtocol.h"

#include <cstring>
#include <iostream>

#include "server/Constants/KeyContants.h"
#include "server/Constants/ProtocolContants.h"

InGameProtocol::InGameProtocol(){
  using namespace ProtocolConstants;

  requestHandlers[PLAYER_MOVEMENT] = [this](const Request &request) {
    return movementHandler(request);
  };
  requestHandlers[ATTACK] = [this](const Request &request) {
    return shootHandler(request);
  };
  requestHandlers[PICK_UP_ITEM] = [this](const Request &request) {
    return pickUpItemHandler(request);
  };
  requestHandlers[DROP_ITEM] = [this](const Request &request) {
    return dropItemHandler(request);
  };
  requestHandlers[BUY] = [this](const Request &request) {
    return buyHandler(request);
  };
  requestHandlers[CHANGE_ANGLE] = [this](const Request &request) {
    return changeAngleHandler(request);
  };
  requestHandlers[SWITCH_WEAPON] = [this](const Request &request) {
    return switchWeaponHandler(request);
  };
  requestHandlers[PLANT_BOMB] = [this](const Request &request) {
    return plantBombHandler(request);
  };
  requestHandlers[DEFUSE_BOMB] = [this](const Request &request) {
    return defuseBombHandler(request);
  };
  requestHandlers[EXIT_GAME] = [this](const Request &request) {
    return exitHandler(request);
  };
}

InGameOrder InGameProtocol::handleRequest(const Request &request) {
    //std::cout << "InGameProtocol::handleRequest. Inicio." << std::endl;
  const uint8_t opCode = request.getRequest().at(opCodeKey).front();
    //std::cout << "InGameProtocol::handleRequest. opCode:" << (int)opCode << std::endl;
  if (!requestHandlers.contains(opCode)) {
    throw -1; // TODO FIX
  }
  return requestHandlers[opCode](request);
}
InGameOrder InGameProtocol::movementHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  uint16_t direction;
  std::memcpy(&direction, message.at(directionKey).data(), sizeof(uint16_t));
  return InGameOrder(ProtocolConstants::PLAYER_MOVEMENT, clientId, direction);
}

InGameOrder InGameProtocol::shootHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  return InGameOrder(ProtocolConstants::ATTACK, clientId);
}

InGameOrder InGameProtocol::pickUpItemHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  return InGameOrder(ProtocolConstants::PICK_UP_ITEM, clientId);
}

InGameOrder InGameProtocol::dropItemHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  return InGameOrder(ProtocolConstants::DROP_ITEM, clientId);
}

InGameOrder InGameProtocol::switchWeaponHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();
  const uint8_t slot = message.at(slotKey).front();
  return InGameOrder(ProtocolConstants::SWITCH_WEAPON, clientId,
                     slot); // weapon, direction, ammout dummys
}

InGameOrder InGameProtocol::changeAngleHandler(const Request &request) {
    //std::cout << "InGameProtocol::changeAngleHandler, entre cambio angulo." << std::endl;
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();
  double angle;
  std::vector<char> serializedAngle = message.at(angleKey);
  std::memcpy(&angle, serializedAngle.data(), sizeof(double));

  return InGameOrder(ProtocolConstants::CHANGE_ANGLE, clientId, angle); // slot, direction, ammout dummys
}

InGameOrder InGameProtocol::buyHandler(const Request &request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();
    uint16_t amount;
    std::memcpy(&amount, message.at(amountKey).data(), sizeof(uint16_t));
    const uint8_t weapon = message.at(weaponKey).front();
    return InGameOrder(ProtocolConstants::BUY, clientId, amount, weapon);
}

InGameOrder InGameProtocol::plantBombHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  return InGameOrder(ProtocolConstants::PLANT_BOMB, clientId);
}

InGameOrder InGameProtocol::defuseBombHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  return InGameOrder(ProtocolConstants::DEFUSE_BOMB, clientId);
}

InGameOrder InGameProtocol::exitHandler(const Request &request) {
  const size_t clientId = request.getId();

  return InGameOrder(ProtocolConstants::EXIT_GAME, clientId);
}

void InGameProtocol::end() {}
