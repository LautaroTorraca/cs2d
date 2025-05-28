#pragma once
#include "../Orders/GameLobbyOrder.h"
#include "../Requests/Request.h"

class GameLobbyProtocolInterface {


public:

    virtual GameLobbyOrder readyHandler(const Request& request);
    virtual GameLobbyOrder exitLobbyHandler(const Request& request);

    virtual ~GameLobbyProtocolInterface() = default;

};

