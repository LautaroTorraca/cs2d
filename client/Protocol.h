#pragma once
#include <string>

#include "common/Constants/SnapshotConstants.h"
#include "common/socket.h"
#include "server/DTO/GameLobbyDTO.h"
#include "server/DTO/LobbyConnectionDTO.h"
#include "server/DTO/PlayerChoicesDTO.h"
#include "server/Readers/Reader.h"
#include "server/Sender/Sender.h"

#include "BuyOrder.h"
#include "GamesList.h"
#include "LobbyDTO.h"
#include "MoveConstants.h"
#include "PositionDTO.h"
#include "WeaponChanger.h"
// #include <sstream>


class Protocol {
    Socket clientSocket;
    Sender sender;
    Reader reader;

public:
    Protocol(const std::string& hostName, const std::string& port);
    void createLobby(const LobbyDTO& lobbyInfo);
    LobbyConnectionDTO getLobbyConnection() const;
    GamesList getGamesList();
    void joinLobby(const LobbyDTO& lobbyInfo);

    void leaveLobby();

    void ready(const PlayerChoicesDTO& playerChoices);
    GameLobbyDTO getGameLobby() const;
    void leaveGameLobby();

    void move(const Direction& direction);
    void attack();
    void pickUp();
    void buy(const BuyOrder& buyOrder);
    void changeAngle(const PositionDTO& positionInfo);
    void changeWeapon(const WeaponChanger& weaponChanger);
    void plantBomb();
    void defuseBomb();
    void exit();
    PlayerChoicesDTO readPlayerChoices() const;
    Snapshot receiveSnapshot() const;
    PreSnapshot receivePreSnapshot() const;
    virtual ~Protocol() = default;
};
