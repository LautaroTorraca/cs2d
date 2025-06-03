#include "InGameProtocol.h"

#include <cstring>

#include "Constants/ProtocolContants.h"
#include "Constants/KeyContants.h"

InGameProtocol::InGameProtocol(
    std::map<size_t, std::unique_ptr<Socket>> &connectedUsers)
    : connectedUsers(connectedUsers) {
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
  const uint8_t opCode = request.getRequest().at(opCodeKey).front();

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

  const uint8_t direction = message.at(directionKey).front();

  return InGameOrder(ProtocolConstants::ATTACK, clientId, direction);
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

  const uint8_t slot = message.at(weaponKey).front();

  return InGameOrder(ProtocolConstants::SWITCH_WEAPON, clientId,
                     slot); // weapon, direction, ammout dummys
}

InGameOrder InGameProtocol::changeAngleHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  double x;
  double y;
  std::vector<char> serializedX = message.at(xPosKey);
  std::vector<char> serializedY = message.at(yPosKey);
  std::memcpy(&x, serializedX.data(), sizeof(double));
  std::memcpy(&y, serializedY.data(), sizeof(double));

  return InGameOrder(ProtocolConstants::CHANGE_ANGLE, clientId, std::pair<double, double>(x, y)); // slot, direction, ammout dummys
}

InGameOrder InGameProtocol::buyHandler(const Request &request) {
  const size_t clientId = request.getId();
  const std::map<std::string, std::vector<char>> message = request.getRequest();

  const uint8_t amount = message.at(ammoAmountKey).front();
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

// NO LA USAMOS NUNCA, REVISAR CUANDO ME LOS TENGO QUE GUARDAR
void InGameProtocol::registerClient(size_t clientId,
                                    std::unique_ptr<InGameHandler> handler) {
  usersInGame.emplace(clientId, std::move(handler));
}

void InGameProtocol::end() { usersInGame.clear(); }
