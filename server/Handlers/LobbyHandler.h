#pragma once
#include <functional>
#include <unordered_map>

#include "../Readers/Reader.h"
#include "../Requests/Request.h"
#include "../common/socket.h"

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
    explicit LobbyHandler(Socket& user, const size_t& userId);
    Request handle(uint8_t opcode) const;

    ~LobbyHandler();
};
