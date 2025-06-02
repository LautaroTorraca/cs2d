//
// Created by lionel on 25/05/25.
//

#include "Game.h"
#include <ranges>
#include "Bomb.h"

void Game::addCounter(const size_t &id, const std::string &name, const Skin& skin) {
    std::shared_ptr<CounterPlayer> counter = std::make_shared<CounterPlayer>(id, name, skin, this->gameParser, this->gameMap);
    this->counters.add(id, counter);
    this->players.emplace(id, counter);
    std::shared_ptr<Entity> entity = counter;
    this->gameMap.spawnCounter(entity);
}

void Game::addTerrorist(const size_t &id, const std::string &name, const Skin& skin) {
    std::shared_ptr<TerroristPlayer> terrorist = std::make_shared<TerroristPlayer>(id, name, skin,this->gameParser, this->gameMap);
    this->terrorists.add(id, terrorist);
    this->players.emplace(id, terrorist);
    std::shared_ptr<Entity> entity = terrorist;
    this->gameMap.spawnTerrorist(entity);

}

Game::Game(GameParser& parser, const uint8_t& rounds):
            terrorists(*this), counters(*this),
            gameParser(std::move(parser)), gameMap(gameParser),
            rounds(rounds), currentRound(1), terroristsWinsRounds(0),
            countersWinsRounds(0), bombPlanted(false), status(BUY_TIME),
            timeUntilStart(this->gameParser.getGameInfo(BUY_TIME_DURATION_KEY)) {
    this->teamAdder.emplace(Team::COUNTER_TERRORISTS, [&] (const size_t& id, const std::string& name, const Skin& skin){this->addCounter(id, name, skin);});
    this->teamAdder.emplace(Team::TERRORISTS, [&] (const size_t& id, const std::string& name, const Skin& skin){this->addTerrorist(id, name, skin);});
    for ( auto& [type, factory] : this->gameParser.getShopFactories() ) {
        this->shop.add(type, factory);
    }
}

void Game::addPlayer(const size_t &id, const std::string& name, const Team& team, const Skin& skin) const {
    if (this->teamAdder.contains(team)) {
        this->teamAdder.at(team)(id, name, skin);
    }
}

void Game::move(const size_t& id, const Coordinate& displacement) {
    //TODO: Despues, implementar un patron state para sacar estos ifs de comprobacion de cada metodo.
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    if ( !this->players.contains(id) ) return;
    std::shared_ptr<Entity> entity = this->players.at(id);
    this->gameMap.move(entity, displacement);
}

void Game::changeAngle(const size_t &id, const Coordinate &coordinate) {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    if ( !this->players.contains(id) ) return; //TODO: Ver si conviente que estas cosas tiren una ecepcion en su lugar
    this->players.at(id)->changeAngle(coordinate);
}

void Game::setWeapon(const size_t &id, const uint8_t &index) {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->setWeapon(index);
}

std::map<Coordinate, Tile> Game::getMap() const {
    return this->gameParser.getMap();
}

void Game::buy(const size_t &id, const ProductType &product) {
    if (this->status != BUY_TIME) return;
    if ( this->players.contains(id) ) {
        Buyer& buyer = *this->players.at(id);
        this->shop.buy(buyer, product);
    }

}

void Game::buy(const size_t &id, const ProductType &product, const uint16_t amount) {
    if (this->status != BUY_TIME) return;
    if ( this->players.contains(id) ) {
        Buyer& buyer = *this->players.at(id);
        this->shop.buy(buyer, product, amount);
    }
}

void Game::takeDrop(const size_t &id) {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->takeDrop(this->gameMap);
}

void Game::attack(const size_t &id) {
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->attack(this->gameMap);
}

void Game::advance(const double &actualTime) {
    if (this->status == BUY_TIME && actualTime >= this->timeUntilStart) this->status = ON_GOING;
    for (auto &player: this->players | std::views::values) {
        player->advance(actualTime);
        player->removeFrom(this->gameMap);
    }
    this->gameMap.advance(actualTime);
    this->terrorists.advance(actualTime);
    this->counters.advance(actualTime);

}

void Game::spawnBomb() {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    double activationDuration = this->gameParser.getWeaponInfo(WeaponType::BOMB, BOMB_ACTIVATION_TIME_KEY);
    double deactivationDuration = this->gameParser.getWeaponInfo(WeaponType::BOMB, BOMB_DEACTIVATION_TIME_KEY);
    std::shared_ptr<Weapon> bomb = std::make_shared<Bomb>(*this, activationDuration, deactivationDuration);
    this->terrorists.spawnBomb(bomb);
}

void Game::deactivateBomb(const size_t& id) {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    this->counters.deactivate(id, this->gameMap);
}


void Game::nextRound(const double& actualTime) {
    this->gameMap.reset(this->gameParser);
    this->counters.reset(this->gameMap);
    this->terrorists.reset(this->gameMap);
    this->bombPlanted = false;
    this->timeUntilStart = actualTime + this->gameParser.getGameInfo(BUY_TIME_DURATION_KEY);
    this->status = BUY_TIME;
    this->currentRound++;
}

void Game::terroristsWins() {
    this->terrorists.giveMoney(this->gameParser.getGameInfo(MONEY_PER_WIN_ROUND_KEY));
    this->status = TERRORISTS_WIN;
    this->terroristsWinsRounds++;
}

void Game::countersWins() {
    this->counters.giveMoney(this->gameParser.getGameInfo(MONEY_PER_WIN_ROUND_KEY));
    status = COUNTERS_WIN;
    this->countersWinsRounds++;
}

void Game::bombHasBeenPlanted() {
    status = BOMB_PLANTED;
    this->bombPlanted = true;
}

void Game::allTerroristsAreDead() {
    if (!this->bombPlanted) {
        this->countersWins();
    }
}

std::vector<PlayerInfoDTO> Game::getPlayersInfo() {
    std::vector<PlayerInfoDTO> playersInfo;
    for (auto &player: this->players | std::views::values) {
        playersInfo.emplace_back(player->getInfo());
    }
    return playersInfo;
}

std::vector<DropDTO> Game::getDrops() const {
    return this->gameMap.getDrops();
}

GameInfoDTO Game::getInfo() {
    std::vector<PlayerInfoDTO> playersInfo = this->getPlayersInfo();
    std::vector<DropDTO> dropsInfo = this->getDrops();
    CoordinateDTO plantedBombPosition = this->gameMap.getExplosivePosition();
    return GameInfoDTO(this->status, this->currentRound, this->countersWinsRounds, this->terroristsWinsRounds, playersInfo, dropsInfo, plantedBombPosition);
}
