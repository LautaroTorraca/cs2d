//
// Created by lionel on 25/05/25.
//

#include "Game.h"

#include <iostream>
#include <ranges>

#include "GameLogic/Weapons/Bomb.h"

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
            rounds(rounds), currentRound(INITIAL_ROUND_COUNT), terroristsWinsRounds(0),
            countersWinsRounds(0), bombPlanted(false), status(BUY_TIME),
            timeUntilStart(this->gameParser.getGameInfo(BUY_TIME_DURATION_KEY)),
            actualTime(0) {
    this->teamAdder.emplace(Team::COUNTER_TERRORISTS, [&] (const size_t& id, const std::string& name, const Skin& skin){this->addCounter(id, name, skin);});
    this->teamAdder.emplace(Team::TERRORISTS, [&] (const size_t& id, const std::string& name, const Skin& skin){this->addTerrorist(id, name, skin);});
    for ( auto& [type, factory] : this->gameParser.getShopFactories() ) {
        this->shop.add(type, factory);
    }
    for (auto&[position, drop] : parser.getDrops()) {
        this->gameMap.place(drop, position);
    }
}

void Game::addPlayer(const size_t &id, const std::string& name, const Team& team, const Skin& skin) const {
    if (this->teamAdder.contains(team)) {
        this->teamAdder.at(team)(id, name, skin);
    }
}

void Game::move(const size_t& id, const Coordinate& displacement) {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    if ( !this->players.contains(id) ) return;
    std::shared_ptr<Entity> entity = this->players.at(id);
    this->gameMap.move(entity, displacement);
}

void Game::changeAngle(const size_t &id, const double& angle) {
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->changeAngle(angle);
}

void Game::setWeapon(const size_t &id, const uint8_t &index) {
    if ( !this->players.contains(id) ) return;
    this->players.at(id)->setWeapon(index);
}

std::vector<std::vector<uint8_t>> Game::getMap() const {
    return this->gameParser.getMap();
}

std::map<ProductType, double> Game::getShopInfo() {
    return this->gameParser.getProductsPrices();
}

void Game::buy(const size_t &id, const ProductType &product) {
    if (this->status != BUY_TIME) return;
    if ( this->players.contains(id) ) {
        Buyer& buyer = *this->players.at(id);
        this->shop.buy(buyer, product);
    }

}

void Game::buy(const size_t &id, const ProductType &product, const uint16_t& amount) {
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
    if (!this->players.contains(id)) return;
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    this->players.at(id)->attack(this->gameMap);
}

void Game::advance(const double &actualTime) {
    this->actualTime = actualTime;
    if (this->status == BUY_TIME && actualTime >= this->timeUntilStart) this->status = ON_GOING;
    for (auto &player: this->players | std::views::values) {
        player->advance(actualTime);
        player->removeFrom(this->gameMap);
    }
    this->gameMap.advance(actualTime);
    this->terrorists.advance(actualTime);
    this->counters.advance(actualTime);

}

void Game::setDeaths(const size_t& index, const uint8_t& deaths) {
    if (!this->players.contains(index)) return;
    this->players.at(index)->setDeaths(deaths);
}

void Game::spawnBomb() {
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
    this->spawnBomb();
}

void Game::restart() {
    this->gameMap.reset(this->gameParser);
    this->terrorists.clear();
    this->counters.clear();
    this->players.clear();
    this->bombPlanted = false;
    this->timeUntilStart =  this->gameParser.getGameInfo(BUY_TIME_DURATION_KEY);
    this->status = BUY_TIME;
    this->currentRound++;
}

void Game::kick(const size_t& id) {
    this->counters.kickOut(id);
    this->terrorists.kickOut(id);
    if (this->players.contains(id)) {
        this->gameMap.remove(this->players.at(id));
        this->players.erase(id);
    }
}
void Game::clearPlayers() {
    this->players.clear();
    this->terrorists.clear();
    this->counters.clear();
    this->terroristsWinsRounds = 0;
    this->countersWinsRounds = 0;
}
void Game::setKills(const size_t& id, const uint8_t& kills) const {
    if (!this->players.contains(id))
        return;
    this->players.at(id)->setKills(kills);
}
void Game::addCollectedMoney(const size_t& id, const uint16_t& collectedMoney) {
    if (!this->players.contains(id))
        return;
    this->players.at(id)->addCollectedMoney(collectedMoney);
}
void Game::setCountersWinRounds(const uint8_t& winRounds) {
    this->countersWinsRounds = winRounds;
}

void Game::setTerroristsWinRounds(const uint8_t& winRounds) {
    this->terroristsWinsRounds = winRounds;
}

void Game::terroristsWins() {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED && this->status != BOMB_EXPLODED) return;
    this->terrorists.giveMoney(this->gameParser.getGameInfo(MONEY_PER_WIN_ROUND_KEY));
    this->counters.giveMoney(this->gameParser.getGameInfo(MONEY_PER_ROUND_KEY));
    this->terroristsWinsRounds++;
    if(this->status == BOMB_EXPLODED) return;
    this->status = TERRORISTS_WIN;
}

void Game::countersWins() {
    if (this->status != ON_GOING && this->status != BOMB_PLANTED) return;
    this->counters.giveMoney(this->gameParser.getGameInfo(MONEY_PER_WIN_ROUND_KEY));
    this->terrorists.giveMoney(this->gameParser.getGameInfo(MONEY_PER_ROUND_KEY));
    this->status = COUNTERS_WIN;
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
void Game::bombExploded() {
    if (this->status != BOMB_PLANTED) return;
    this->status = GameStatus::BOMB_EXPLODED;
    this->terroristsWins();
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
    double explosiveTimer = this->gameMap.getExplosiveTime();
    return GameInfoDTO(this->status, this->currentRound, this->countersWinsRounds, this->terroristsWinsRounds, playersInfo, dropsInfo, plantedBombPosition, explosiveTimer, this->actualTime, this->rounds);
}
