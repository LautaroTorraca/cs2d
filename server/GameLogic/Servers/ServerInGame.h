#pragma once

#include <functional>
#include <map>
#include <memory>

#include "server/Constants/Movement.h"
#include "common/DTO/GameLobbyDTO.h"
#include "common/DTO/PlayerChoicesDTO.h"
#include "server/GameLogic/Game.h"
#include "server/Interfaces/InGameProtocolInterface.h"
#include "server/Monitor/GameMonitor.h"
#include "server/Orders/InGameOrder.h"

#include "common/queue.h"

class ServerInGame {
    std::map<OrderType, std::function<void(InGameOrder&)>> translator;
    std::map<std::string, std::shared_ptr<GameMonitor>> games;
    std::map<size_t, std::string> playerToGame;
    std::map<Movement, Coordinate> movements;
    InGameProtocolInterface& protocol;
    std::thread eraserThread;
    Queue<std::string> gamesToErase;
    std::mutex mutex;
    std::function<void(const size_t&)> eraser;
    void setupTranslators();
    void move(const InGameOrder &order);
    void attack(const InGameOrder & order);
    void pickUp(const InGameOrder & order);
    void buy(const InGameOrder & order);
    void changeAngle(const InGameOrder & order);
    void changeWeapon(const InGameOrder & order);
    void plantBomb(const InGameOrder & order);
    void defuseBomb(const InGameOrder& order);
    std::vector<size_t> getGameIds(std::string gameName);
    void eraseGame(const std::string& gameName);
    void exit(const InGameOrder& order);
    void erase();

public:
    explicit ServerInGame(InGameProtocolInterface& protocol, const std::function<void(const size_t&)>& eraser);
    void handle(const std::unique_ptr<Order>& order) const;
    void addNewGame(std::string& gameName, const GameLobbyDTO& gameInfo);
    void leaveGameLobby(const size_t& id);
    ~ServerInGame();
};
