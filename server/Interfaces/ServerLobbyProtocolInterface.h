#pragma once

#include "common/DTO/GamesListDTO.h"
#include "common/DTO/LobbyConnectionDTO.h"

#include "Disconnectable.h"

class ServerLobbyProtocolInterface : public Disconnectable {

public:
  virtual void sendGamesList(GamesListDTO &gamesList) = 0;
  virtual void sendLobbyConnectionStatus(const LobbyConnectionDTO & lobbyConnection) = 0;
  virtual ~ServerLobbyProtocolInterface() = default;
};
