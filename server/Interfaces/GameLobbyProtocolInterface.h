#pragma once
#include "../Orders/GameLobbyOrder.h"
#include "../Requests/Request.h"

class GameLobbyProtocolInterface {

public:
  virtual GameLobbyOrder ready(const Request &request) = 0;
  virtual GameLobbyOrder exitLobby(const Request &request) = 0;

  virtual ~GameLobbyProtocolInterface() = default;
};
