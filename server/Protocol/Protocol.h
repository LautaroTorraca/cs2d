#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <functional>

#include "../common/socket.h"
#include <map>
#include <memory>

#include "ClientHandler.h"
#include "GameLobbyProtocol.h"
#include "InGameProtocol.h"
#include "ServerLobbyProtocol.h"
#include "SnapshotConstants.h"
#include "../common/thread.h"
#include "../common/queue.h"
#include "../Requests/Request.h"

#include "../Interfaces/ServerLobbyProtocolInterface.h"
#include "../Interfaces/GameLobbyProtocolInterface.h"
#include "../Interfaces/InGameProtocolInterface.h"


class Protocol: public ServerLobbyProtocolInterface, GameLobbyProtocolInterface ,InGameProtocolInterface{
protected:
    Socket acceptorSocket;
    std::thread acceptorThread;

    ServerLobbyProtocol lobbyProtocol;
    GameLobbyProtocol gameLobbyProtocol;
    InGameProtocol inGameProtocol;

    std::map<size_t, std::unique_ptr<Socket>> connectedUsers;
    std::map<size_t, std::unique_ptr<ClientHandler>> clientsHandlers;
    std::map<uint8_t, std::function<std::unique_ptr<Order>(const Request&)>> requestMapper;
    Queue<std::shared_ptr<Request>> requestsQueue;

    // std::map<std::string, size_t> games; TODO revisar
    void setupLobbyHandlers();
    void setupGameLobbyHandlers();
    void setupInGameHandlers();

    void handleNewConnection();

public:
    explicit Protocol(const std::string& port);

    std::unique_ptr<Order> getNextOrder();

    ServerLobbyOrder sendGamesList(const Request& request);
    ServerLobbyOrder join(const Request& request);
    ServerLobbyOrder create(const Request& request);
    ServerLobbyOrder disconnect(const Request& request);

    GameLobbyOrder ready(const Request& request);
    GameLobbyOrder exitLobby(const Request& request);

    InGameOrder movement(const Request& request);
    InGameOrder shoot(const Request& request);
    InGameOrder pickUpItem(const Request& request);
    InGameOrder dropItem(const Request& request);
    InGameOrder buyAmmo(const Request& request);
    InGameOrder buyWeapon(const Request& request);
    InGameOrder switchWeapon(const Request& request);
    InGameOrder plantBomb(const Request& request);
    InGameOrder defuseBomb(const Request& request);
    InGameOrder exit(const Request& request);

    void sendSnapshot(const Snapshot& snapshot, const size_t& userId);
    void sendPreSnapshot(const PreSnapshot& preSnapshot, const size_t& userId);

    void end();

    ~Protocol() override;


};



#endif //PROTOCOL_H
