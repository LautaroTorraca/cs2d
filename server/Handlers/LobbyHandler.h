#pragma once
#include <unordered_map>
#include <functional>
#include "../common/socket.h"
#include "../Requests/Request.h"
#include "Readers/Reader.h"

class LobbyHandler {
    Socket& userSocket;
    size_t userId;
    Reader reader;

    std::unordered_map<uint8_t, std::function<Request()>> requestMapper;

    Request createRequest() const;
    Request joinRequest() const;
    Request listGamesRequest();
    Request disconnectRequest();

public:
    explicit LobbyHandler(Socket& user, const size_t &userId);
    Request handle(uint8_t opcode) const;

    ~LobbyHandler();
};
