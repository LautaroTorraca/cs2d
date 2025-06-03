#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Game.h"
#include "GameLobbyDTO.h"
#include "InGameProtocolInterface.h"
#include "PlayerChoicesDTO.h"
#include "Movement.h"
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
    void buyAmmo(const InGameOrder & order);
    void buyWeapon(const InGameOrder & order);
    void changeWeapon(const InGameOrder & order);
    void plantBomb(const InGameOrder & order);
    void defuseBomb(const InGameOrder & order);
    void exit(const InGameOrder & order);

public:
    explicit ServerInGame(InGameProtocolInterface& protocol);
    void handle(const std::unique_ptr<Order>& order) const;
    void addNewGame(std::string& gameName, const GameLobbyDTO& gameInfo);
};
