#pragma once
#include <string>

#include "common/Constants/SnapshotConstants.h"
#include "common/DTO/GameLobbyDTO.h"
#include "common/DTO/LobbyConnectionDTO.h"
#include "common/DTO/PlayerChoicesDTO.h"
#include "common/Readers/Reader.h"
#include "common/Sender/Sender.h"
#include "common/socket.h"

#include "BuyOrder.h"
#include "GamesList.h"
#include "LobbyDTO.h"
#include "MoveConstants.h"
#include "WeaponChanger.h"

namespace Client {
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
    void changeAngle(const double& angle);
    void changeWeapon(const WeaponChanger& weaponChanger);
    void plantBomb();
    void defuseBomb();
    void exit();
    PlayerChoicesDTO readPlayerChoices() const;
    Snapshot receiveSnapshot() const;
    PreSnapshot receivePreSnapshot() const;
    virtual ~Protocol() = default;
};
}  // namespace Client
