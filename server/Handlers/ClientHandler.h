#pragma once

#include "../common/socket.h"
#include "../common/thread.h"
#include "../common/queue.h"
#include "../Requests/Request.h"

#include "LobbyHandler.h"

#include <functional>
#include <unordered_map>

#include "GameLobbyHandler.h"
#include "InGameHandler.h"
#include "SnapshotConstants.h"

class ClientHandler final : public Thread {
    Socket& userSocket;
    size_t id;
    Queue<std::shared_ptr<Request>>& requestsQueue;

    LobbyHandler lobbyHandler;
    GameLobbyHandler gameLobbyHandler;
    InGameHandler inGameHandler;

    std::unordered_map<uint8_t, std::function<Request()>> opcodeDispatcher;

    void registerOpcodes();

public:
    ClientHandler(Socket& socket, const size_t& clientId, Queue<std::shared_ptr<Request>>& requestQueue);

    void run() override;

    ~ClientHandler() override;

    void sendSnapshot(const Snapshot & snapshot);
    void sendPreSnapshot(const PreSnapshot & preSnapshot);
};
