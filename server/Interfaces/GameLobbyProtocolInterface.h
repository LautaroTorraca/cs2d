#pragma once
#include "DTO/GameLobbyDTO.h"

#include "Disconnectable.h"

class GameLobbyProtocolInterface: public Disconnectable {

public:
    virtual void sendLobby(const GameLobbyDTO& gameLobbyInfo) = 0;

    virtual ~GameLobbyProtocolInterface() = default;
};
