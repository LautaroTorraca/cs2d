#pragma once

#include "../Orders/ServerLobbyOrder.h"
#include "../Requests/Request.h"

class ServerLobbyProtocolInterface {

public:
  virtual ServerLobbyOrder sendGamesList(const Request &request) = 0;
  virtual ServerLobbyOrder join(const Request &request) = 0;
  virtual ServerLobbyOrder create(const Request &request) = 0;
  virtual ServerLobbyOrder disconnect(const Request &request) = 0;

  virtual ~ServerLobbyProtocolInterface() = default;
};
