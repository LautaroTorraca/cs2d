//
// Created by lionel on 25/05/25.
//

#include "Game.h"
#include <ranges>

void Game::addCounter(const size_t &id, const std::string &name) {
    std::shared_ptr<CounterPlayer> counter = std::make_shared<CounterPlayer>(id, name, this->gameParser, this->gameMap);
    this->counters.add(id, counter);
    this->players.emplace(id, counter);
    std::shared_ptr<Entity> entity = counter;
    this->gameMap.spawnCounter(entity);
}

void Game::addTerrorist(const size_t &id, const std::string &name) {
    std::shared_ptr<TerroristPlayer> terrorist = std::make_shared<TerroristPlayer>(id, name, this->gameParser, this->gameMap);
    this->terrorists.add(id, terrorist);
    this->players.emplace(id, terrorist);
    std::shared_ptr<Entity> entity = terrorist;
    this->gameMap.spawnTerrorist(entity);

}

Game::Game(GameParser& parser, const uint8_t& rounds): gameParser(std::move(parser)), gameMap(gameParser), rounds(rounds)  {
    this->teamAdder.emplace(Team::COUNTER_TERRORISTS, [&] (const size_t& id, const std::string& name){this->addCounter(id, name);});
    this->teamAdder.emplace(Team::TERRORISTS, [&] (const size_t& id, const std::string& name){this->addTerrorist(id, name);});
    for ( auto& [type, factory] : this->gameParser.getShopFactories() ) {
        this->shop.add(type, factory);
    }
}

void Game::addPlayer(const size_t &id, const std::string& name, const Team& team) const {
    if (this->teamAdder.contains(team)) {
        this->teamAdder.at(team)(id, name);
    }
}

void Game::move(const size_t& id, Coordinate& displacement) {
    if ( !this->players.contains(id) ) return;
    std::shared_ptr<Entity> entity = this->players.at(id);
    this->gameMap.move(entity, displacement);
}

void Game::changeAngle(size_t &id, Coordinate &coordinate) {
    if ( !this->players.contains(id) ) return; //TODO: Ver si conviente que estas cosas tiren una ecepcion en su lugar
    this->players.at(id)->changeAngle(coordinate);
}

void Game::setWeapon(const size_t &id, const uint8_t &index) {
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->setWeapon(index);
}

std::map<Coordinate, Tile> Game::getMap() {
    return this->gameParser.getMap();
}

void Game::buy(const size_t &id, const ProductTypes &product) {
    if ( this->players.contains(id) ) {
        Buyer& buyer = *this->players.at(id);
        this->shop.buy(buyer, product);
    }

}

void Game::takeDrop(const size_t &id) {
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->takeDrop(this->gameMap);
}

void Game::attack(const size_t &id, const Coordinate &coordinate) {
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->attack(this->gameMap, coordinate);
}

std::vector<PlayerInfoDTO> Game::getPlayersInfo() {
    std::vector<PlayerInfoDTO> playersInfo;
    for (auto &player: this->players | std::views::values) {
        playersInfo.emplace_back(player->getInfo());
    }
    return playersInfo;
}

std::vector<DropDTO> Game::getDrops() {
    return this->gameMap.getDrops();
}
