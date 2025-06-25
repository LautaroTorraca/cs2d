//
// Created by lionel on 25/05/25.
//

#ifndef GAME_H
#define GAME_H
#include <functional>
#include <map>
#include <memory>
#include <variant>

#include "Constants/GameStatus.h"
#include "DTO/DropDTO.h"
#include "GameLogic/Interfaces/Finalizable.h"
#include "GameLogic/Shop/Shop.h"
#include "Orders/InGameOrder.h"
#include "common/Constants/Team.h"
#include "common/DTO/PlayerInfoDTO.h"
#include "server/GameLogic/Player/CountersTeam.h"
#include "server/GameLogic/Player/Player.h"
#include "server/GameLogic/Player/TerroristsTeam.h"

#include "GameInfoDTO.h"
#include "GameMap.h"
#include "GameParser.h"

#define BUY_TIME_DURATION_KEY "buyTimeDuration"
#define MONEY_PER_WIN_ROUND_KEY "moneyPerWinRound"
#define MONEY_PER_ROUND_KEY "moneyPerRound"
#define INITIAL_ROUND_COUNT 1

class Game : public Advancer, public Finalizable {
    std::map<size_t, std::shared_ptr<Player>> players;
    TerroristsTeam terrorists;
    CountersTeam counters;
    GameParser gameParser;
    GameMap gameMap;
    Shop shop;
    const uint8_t rounds;
    uint8_t currentRound;
    uint8_t terroristsWinsRounds;
    uint8_t countersWinsRounds;
    bool bombPlanted;
    GameStatus status;
    double timeUntilStart;
    std::map<Team, std::function<void(const size_t&, const std::string&, const Skin&)>> teamAdder;
    double actualTime;
    void addCounter(const size_t &id, const std::string &name, const Skin &skin);
    void addTerrorist(const size_t &id, const std::string &name, const Skin &skin);
public:
    Game(GameParser& parser, const uint8_t& rounds);
    void addPlayer(const size_t &id, const std::string &name, const Team &team, const Skin &skin) const;
    void move(const size_t& id, const Coordinate& displacement);
    void changeAngle(const size_t& id, const double& angle);
    void setWeapon(const size_t& id, const uint8_t& index);
    [[nodiscard]] std::vector<std::vector<uint8_t>> getMap() const;
    std::map<ProductType, double> getShopInfo();
    void buy(const size_t& id, const ProductType& product);
    void buy(const size_t& id, const ProductType& product, const uint16_t& amount);
    void takeDrop(const size_t& id);
    void attack(const size_t& id);
    void advance(const double& actualTime) override;
    void setDeaths(const size_t& index, const uint8_t& deaths);
    void spawnBomb();
    void deactivateBomb(const size_t& id);
    void terroristsWins() override;
    void countersWins() override;
    void bombHasBeenPlanted() override;
    void allTerroristsAreDead() override;
    void bombExploded() override;
    std::vector<PlayerInfoDTO> getPlayersInfo();
    [[nodiscard]] std::vector<DropDTO> getDrops() const;
    GameInfoDTO getInfo();
    void nextRound(const double& actualTime);
    void restart();
    void kick(const size_t& id);
    void clearPlayers();
    void setKills(const size_t& id, const uint8_t& kills) const;
    void addCollectedMoney(const size_t& id, const uint16_t& collectedMoney);
    void setCountersWinRounds(const uint8_t& winRounds);
    void setTerroristsWinRounds(const uint8_t& winRounds);
};



#endif //GAME_H
