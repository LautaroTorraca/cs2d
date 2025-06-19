#pragma once

#include <functional>
#include <unordered_map>

#include "../DTO/GameLobbyDTO.h"
#include "../Interfaces/DisconnectableProtocol.h"
#include "../Requests/Request.h"
#include "../common/queue.h"
#include "../common/socket.h"
#include "../common/thread.h"
#include "Constants/SnapshotConstants.h"
#include "DTO/LobbyConnectionDTO.h"
#include "Sender/Sender.h"

#include "GameInfoDTO.h"
#include "GameLobbyHandler.h"
#include "InGameHandler.h"
#include "LobbyHandler.h"

class ClientHandler final : public Thread {
    Socket userSocket;
    size_t id;
    Queue<std::shared_ptr<Request>> &requestsQueue;

    LobbyHandler lobbyHandler;
    GameLobbyHandler gameLobbyHandler;
    InGameHandler inGameHandler;
    Sender sender;
    std::unordered_map<uint8_t, std::function<Request()>> opcodeDispatcher;
    DisconnectableProtocol& disconnectable;

  void registerOpcodes();

public:
  ClientHandler(Socket& socket, const size_t &clientId,
                Queue<std::shared_ptr<Request>> &requestQueue, DisconnectableProtocol& disconnectable);

  void run() override;

  ~ClientHandler() override;

  void sendSnapshot(const GameInfoDTO &gameInfo);
  void sendPreSnapshot(const PreSnapshot &preSnapshot);
  void stopService();
  void sendGamesList(const std::vector<std::string> & gamesList);
  void sendGameLobby(const GameLobbyDTO & gameLobbyInfo);

  void sendLobbyConnectonStatus(const LobbyConnectionDTO & lobbyConnection);
};
