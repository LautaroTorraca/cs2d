#pragma once

#include "../Requests/Request.h"
#include "Orders/InGameOrder.h"
#include "Handlers/InGameHandler.h"
#include <map>
#include <memory>
#include <functional>


class InGameProtocol {
    std::map<size_t, std::unique_ptr<Socket>>& connectedUsers;
    std::map<size_t, std::unique_ptr<InGameHandler>> usersInGame;
    std::map<uint8_t, std::function<InGameOrder(const Request&)>> requestHandlers;

    InGameOrder movementHandler(const Request& request);
    InGameOrder shootHandler(const Request& request);
    InGameOrder pickUpItemHandler(const Request& request);
    InGameOrder dropItemHandler(const Request& request);
    InGameOrder buyAmmoHandler(const Request& request);
    InGameOrder buyWeaponHandler(const Request& request);
    InGameOrder switchWeaponHandler(const Request& request);
    InGameOrder plantBombHandler(const Request& request);
    InGameOrder defuseBombHandler(const Request& request);
    InGameOrder exitHandler(const Request& request);

public:
    explicit InGameProtocol(std::map<size_t, std::unique_ptr<Socket>>& connectedUsers);

    InGameProtocol(const InGameProtocol&) = delete;
    InGameProtocol& operator=(const InGameProtocol&) = delete;
    InGameProtocol(InGameProtocol&&) = delete;
    InGameProtocol& operator=(InGameProtocol&&) = delete;

    InGameOrder handleRequest(const Request& request);

    void registerClient(size_t clientId, std::unique_ptr<InGameHandler> handler);
    void end();
};
