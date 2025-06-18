//
// Created by lionel on 02/06/25.
//

#ifndef GAMEMONITOR_H
#define GAMEMONITOR_H
#include "thread.h"
#include "server/Game.h"
#include "server/Interfaces/InGameProtocolInterface.h"


class GameMonitor : public Thread {
    Game game;
    std::mutex mutex;
    uint8_t rounds;
    InGameProtocolInterface& protocol;
public:
    GameMonitor(GameParser& parser, const uint8_t& rounds, InGameProtocolInterface& protocol) : game(parser, rounds), rounds(rounds), protocol(protocol) {}

    void addPlayer(const size_t &id, const std::string &name, const Team &team, const Skin &skin);
    void move(const size_t& id, const Coordinate& displacement);
    void changeAngle(const size_t& id, const double& angle);
    void setWeapon(const size_t& id, const uint8_t& index);
    [[nodiscard]] std::vector<std::vector<uint8_t>> getMap();
    void buy(const size_t& id, const ProductType& product);
    void buy(const size_t& id, const ProductType& product, uint16_t amount);
    void takeDrop(const size_t& id);
    void attack(const size_t& id);
    void spawnBomb();
    void deactivateBomb(const size_t& id);
    GameInfoDTO getInfo();
    void kick(const size_t& id);

    void sendPreSnapshot();
    void run() override;

};



#endif //GAMEMONITOR_H
