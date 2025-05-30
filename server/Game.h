//
// Created by lionel on 25/05/25.
//

#ifndef GAME_H
#define GAME_H
#include <functional>
#include <map>
#include <memory>

#include "CountersTeam.h"
#include "GameMap.h"
#include "Player.h"
#include "Team.h"
#include "TerroristsTeam.h"
#include "GameParser.h"
#include "PlayerInfoDTO.h"
#include "Shop.h"
#include "DropDTO.h"


class Game {
    std::map<size_t, std::shared_ptr<Player>> players;
    TerroristsTeam terrorists;
    CountersTeam counters;
    GameParser gameParser;
    GameMap gameMap;
    Shop shop;
    uint8_t rounds;
    std::map<Team, std::function<void(const size_t&, const std::string&)>> teamAdder;
    void addCounter(const size_t& id, const std::string& name);
    void addTerrorist(const size_t& id, const std::string& name);
public:
    Game(GameParser& parser, const uint8_t& rounds);
    void addPlayer(const size_t& id, const std::string& name, const Team& team) const;
    void move(const size_t& id, Coordinate& displacement);
    void changeAngle(size_t& id, Coordinate& coordinate);
    void setWeapon(const size_t& id, const uint8_t& index);
    std::map<Coordinate, Tile> getMap();
    void buy(const size_t& id, const ProductTypes& product);
    void takeDrop(const size_t& id);
    void attack(const size_t& id, const Coordinate & coordinate);
    std::vector<PlayerInfoDTO> getPlayersInfo();
    std::vector<DropDTO> getDrops();
};



#endif //GAME_H
