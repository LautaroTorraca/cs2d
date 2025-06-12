//
// Created by lionel on 25/05/25.
//

#ifndef GAME_H
#define GAME_H
#include <functional>
#include <map>
#include <memory>
#include <variant>

#include "Orders/InGameOrder.h"

#include "CountersTeam.h"
#include "DropDTO.h"
#include "Finalizable.h"
#include "GameInfoDTO.h"
#include "GameMap.h"
#include "GameParser.h"
#include "GameStatus.h"
#include "Player.h"
#include "PlayerInfoDTO.h"
#include "Shop.h"
#include "Team.h"
#include "TerroristsTeam.h"

#define BUY_TIME_DURATION_KEY "buyTimeDuration"
#define MONEY_PER_WIN_ROUND_KEY "moneyPerWinRound"

class Game: public Advancer, public Finalizable {
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
    void addCounter(const size_t& id, const std::string& name, const Skin& skin);
    void addTerrorist(const size_t& id, const std::string& name, const Skin& skin);

public:
    Game(GameParser& parser, const uint8_t& rounds);
    void addPlayer(const size_t& id, const std::string& name, const Team& team,
                   const Skin& skin) const;
    void move(const size_t& id, const Coordinate& displacement);
    void changeAngle(const size_t& id, const Coordinate& coordinate);
    void setWeapon(const size_t& id, const uint8_t& index);
    [[nodiscard]] std::vector<std::vector<uint8_t>> getMap() const;
    void buy(const size_t& id, const ProductType& product);
    void buy(const size_t& id, const ProductType& product, const uint16_t& amount);
    void takeDrop(const size_t& id);
    void attack(const size_t& id);
    void advance(const double& actualTime) override;
    void spawnBomb();
    void deactivateBomb(const size_t& id);
    void terroristsWins() override;
    void countersWins() override;
    void bombHasBeenPlanted() override;
    void allTerroristsAreDead() override;
    std::vector<PlayerInfoDTO> getPlayersInfo();
    [[nodiscard]] std::vector<DropDTO> getDrops() const;
    GameInfoDTO getInfo();
    void nextRound(const double& actualTime);
    void restart();
    void kick(const size_t& id);
};


#endif  // GAME_H
