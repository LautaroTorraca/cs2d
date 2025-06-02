#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <functional>

#include "../common/socket.h"
#include <map>
#include <memory>

#include "../Requests/Request.h"
#include "../common/queue.h"
#include "Constants/SnapshotConstants.h"
#include "GameLobbyProtocol.h"
#include "Handlers/ClientHandler.h"
#include "InGameProtocol.h"
#include "ServerLobbyProtocol.h"

#include "../Interfaces/GameLobbyProtocolInterface.h"
#include "../Interfaces/InGameProtocolInterface.h"
#include "../Interfaces/ServerLobbyProtocolInterface.h"

class Protocol : public ServerLobbyProtocolInterface,
                 public GameLobbyProtocolInterface,
                 public InGameProtocolInterface {
protected:
  Socket acceptorSocket;
  std::thread acceptorThread;

  ServerLobbyProtocol lobbyProtocol;
  GameLobbyProtocol gameLobbyProtocol;
  InGameProtocol inGameProtocol;
  size_t handledUsers;

  std::map<size_t, std::unique_ptr<Socket>> connectedUsers;
  std::map<size_t, std::unique_ptr<ClientHandler>> clientsHandlers;
  std::map<uint8_t, std::function<std::unique_ptr<Order>(const Request &)>>
      requestMapper;
  Queue<std::shared_ptr<Request>> requestsQueue;

  // std::map<std::string, size_t> games; TODO revisar
  void setupLobbyHandlers();
  void setupGameLobbyHandlers();
  void setupInGameHandlers();

  void handleNewConnection();

public:
  explicit Protocol(const std::string &port);

  std::unique_ptr<Order> getNextOrder();

  void sendGamesList(GamesListDTO &gamesList) override;

  void disconnect(const DisconnectionDTO &disconnectionInfo) override;

  GameLobbyOrder ready(const Request &request) override;
  GameLobbyOrder exitLobby(const Request &request) override;
  void sendSnapshot(const Snapshot &snapshot, const size_t &userId);
  void sendPreSnapshot(const PreSnapshot &preSnapshot, const size_t &userId);

  void end();

  ~Protocol() override;
};

#endif // PROTOCOL_H
