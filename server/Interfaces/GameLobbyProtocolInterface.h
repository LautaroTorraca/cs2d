#pragma once
#include "Disconnectable.h"
#include "DTO/GameLobbyDTO.h"

class GameLobbyProtocolInterface : public Disconnectable {

public:
  virtual void sendLobby(const GameLobbyDTO& gameLobbyInfo) = 0;

  virtual ~GameLobbyProtocolInterface() = default;
};
