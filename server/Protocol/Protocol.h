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

class ProtocolTesting : public ServerLobbyProtocolInterface,
                        GameLobbyProtocolInterface,
                        InGameProtocolInterface {
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

  void setupLobbyHandlers();
  void setupGameLobbyHandlers();
  void setupInGameHandlers();

  void handleNewConnection();

public:
  explicit ProtocolTesting(const std::string &port);

  std::unique_ptr<Order> getNextOrder();

  void sendGamesList(GamesListDTO &gamesList) override;
  void sendLobbyConnectionStatus(const LobbyConnectionDTO & lobbyConnection) override;

  void disconnect(const DisconnectionDTO &disconnectionInfo) override;

  std::vector<size_t> getIds(const GameLobbyDTO &gameLobbyInfo);

  void sendLobby(const GameLobbyDTO &gameLobbyInfo) override;

  std::vector<size_t> getSnapshotIds(const std::vector<PlayerInfoDTO> &playerInfos);

  void sendSnapshot(const GameInfoDTO & gameInfo);
  void sendPreSnapshot(const PreSnapshot &preSnapshot) override;

  void end();

  ~ProtocolTesting() override;
};

#endif // PROTOCOL_H
