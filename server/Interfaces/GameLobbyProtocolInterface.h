#pragma once
#include "Disconnectable.h"
#include "server/DTO/GameLobbyDTO.h"

class GameLobbyProtocolInterface : public Disconnectable {

public:
  virtual void sendLobby(const GameLobbyDTO& gameLobbyInfo) = 0;

    ~GameLobbyProtocolInterface() override = default;
};
