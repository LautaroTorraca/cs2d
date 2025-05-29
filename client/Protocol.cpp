#include "Protocol.h"
#include "server/Constants/ProtocolContants.h"
#include <string>

#include "common/Constants/SnapshotConstants.h"

Protocol::Protocol(const std::string &port, const std::string &hostName)
    : clientSocket(hostName.c_str(), port.c_str()) {}

void Protocol::move(const Direction &direction) {

  const uint8_t opCode = ProtocolConstants::PLAYER_MOVEMENT;

  clientSocket.sendall(&opCode, sizeof(opCode));
  clientSocket.sendall(&direction, sizeof(direction));
}

// TODO ARREGLAR EN COMO *** VAMOS A RECIBIR LA SNAPSHOT, PERO PARA ESO NECESITO
// QUE MI TIM ME LO DIGA COMO ME LO MANDA :) => necesito saber como mandarlo
// para recibir
Snapshot Protocol::receiveSnapshot() {
  Snapshot snapshot;
  clientSocket.recvall(&snapshot, sizeof(snapshot));

  return snapshot;
}

PreSnapshot Protocol::receivePreSnapshot() {
  PreSnapshot preSnapshot;
  clientSocket.recvall(&preSnapshot, sizeof(preSnapshot));

  return preSnapshot;
}
