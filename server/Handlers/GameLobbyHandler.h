#pragma once
#include <functional>
#include <unordered_map>

#include "server/Requests/Request.h"
#include "common/socket.h"
#include "common/Readers/Reader.h"

class GameLobbyHandler {

    Socket& userSocket;
    size_t userId;
    Reader reader;

    std::unordered_map<uint8_t, std::function<Request()>> requestMapper;

    Request readyRequest() const;
    Request exitGameLobbyRequest() const;

public:
    explicit GameLobbyHandler(Socket& user, const size_t &userId);
    Request handle(uint8_t opcode) const;

    ~GameLobbyHandler();

};
