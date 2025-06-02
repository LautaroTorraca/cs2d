#pragma once

#include "Disconnectable.h"
#include "GamesListDTO.h"

class ServerLobbyProtocolInterface : public Disconnectable {

public:
  virtual void sendGamesList(GamesListDTO &gamesList) = 0;
  virtual ~ServerLobbyProtocolInterface() = default;
};
