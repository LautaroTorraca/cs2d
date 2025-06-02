#pragma once

#include "Disconnectable.h"
#include "GamesListDTO.h"
#include "LobbyConnectionDTO.h"

class ServerLobbyProtocolInterface : public Disconnectable {

public:
  virtual void sendGamesList(GamesListDTO &gamesList) = 0;
  virtual void sendLobbyConnectionStatus(const LobbyConnectionDTO & lobbyConnection) = 0;
  virtual ~ServerLobbyProtocolInterface() = default;
};
