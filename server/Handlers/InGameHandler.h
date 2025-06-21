#pragma once
#include <unordered_map>
#include <functional>
#include "../common/socket.h"
#include "../Requests/Request.h"
#include "server/Readers/Reader.h"


class InGameHandler {

    Socket& userSocket;
    size_t userId;
    Reader reader;

    std::unordered_map<uint8_t, std::function<Request()>> requestMapper;

    Request moveRequest() const;
    Request shootRequest() const;
    Request pickUpItemRequest() const;
    Request dropItemRequest() const;
    Request buyRequest() const;
    Request changeAngleRequest() const;
    Request switchWeaponsRequest() const;
    Request plantBombRequest() const;
    Request defuseBombRequest() const;
    Request exitGameRequest() const;




public:
    explicit InGameHandler(Socket& user, const size_t &userId);
    Request handle(uint8_t opcode) const;

    ~InGameHandler();

};



