#pragma once

#include "server/Requests/Request.h"
#include "server/Orders/InGameOrder.h"
#include <map>
#include <memory>
#include <functional>


class InGameProtocol {
    std::map<uint8_t, std::function<InGameOrder(const Request&)>> requestHandlers;

    InGameOrder movementHandler(const Request& request);
    InGameOrder shootHandler(const Request& request);
    InGameOrder pickUpItemHandler(const Request& request);
    InGameOrder dropItemHandler(const Request& request);
    InGameOrder buyHandler(const Request& request);
    InGameOrder changeAngleHandler(const Request& request);
    InGameOrder switchWeaponHandler(const Request& request);
    InGameOrder plantBombHandler(const Request& request);
    InGameOrder defuseBombHandler(const Request& request);
    InGameOrder exitHandler(const Request& request);

public:
    explicit InGameProtocol();

    InGameProtocol(const InGameProtocol&) = delete;
    InGameProtocol& operator=(const InGameProtocol&) = delete;
    InGameProtocol(InGameProtocol&&) = delete;
    InGameProtocol& operator=(InGameProtocol&&) = delete;

    InGameOrder handleRequest(const Request& request);
    void end();
};
