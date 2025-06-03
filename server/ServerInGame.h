#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Game.h"
#include "DTO/GameLobbyDTO.h"
#include "Interfaces/InGameProtocolInterface.h"
#include "DTO/PlayerChoicesDTO.h"
#include "Constants/Movement.h"
#include "Orders/InGameOrder.h"

class ServerInGame {
    std::map<OrderType, std::function<void(InGameOrder&)>> translator;
    std::map<std::string, Game> games;
    std::map<size_t, std::string> playerToGame;
    std::map<Movement, Coordinate> movements;
    InGameProtocolInterface& protocol;
    void setupTranslators();
    void move(const InGameOrder &order);
    void attack(const InGameOrder & order);
    void pickUp(const InGameOrder & order);
    void buy(const InGameOrder & order);
    void changeAngle(const InGameOrder & order);
    void changeWeapon(const InGameOrder & order);
    void plantBomb(const InGameOrder & order);
    void defuseBomb(const InGameOrder & order);
    void exit(const InGameOrder & order);

public:
    explicit ServerInGame(InGameProtocolInterface& protocol);
    void handle(const std::unique_ptr<Order>& order) const;
    void addNewGame(std::string& gameName, const GameLobbyDTO& gameInfo);
    void leaveGameLobby(const size_t& id);
};
