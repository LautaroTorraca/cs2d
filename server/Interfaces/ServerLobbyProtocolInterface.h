#pragma once

#include "../Orders/ServerLobbyOrder.h"
#include "../Requests/Request.h"

class ServerLobbyProtocolInterface {

public:

    virtual ServerLobbyOrder sendGamesListHandler(const Request& request) const;
    virtual ServerLobbyOrder joinHandler(const Request& request);
    virtual ServerLobbyOrder createHandler(const Request& request);
    virtual ServerLobbyOrder disconnectHandler(const Request& request);

    virtual ~ServerLobbyProtocolInterface() = default;

};
