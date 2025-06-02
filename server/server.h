#pragma once
#include <map>

#include <functional>
#include <memory>

#include "Orders/OrderType.h"

#include "Protocol/Protocol.h"
#include "ServerGameLobby.h"
#include "ServerInGame.h"
#include "ServerLobby.h"

class Server {
  ProtocolTesting protocol;

  ServerLobby serverLobby;
  ServerGameLobby gameLobbyServer;
  ServerLobby serverLobby;

  std::map<OrderType, std::function<void(std::unique_ptr<Order> &)>>
      orderTranslator;

  void setupLobbyOrders();
  void setupGameLobbyOrders();
  void setupInGameOrders();

public:
  explicit Server(const char *port);
  void run();

  // TODO ARREGLAR
  // void shutdown() const;
  //~Server();
};
