//
// Created by lionel on 02/06/25.
//

#include "GameMonitor.h"

#include "common/Constants/SnapshotConstants.h"

#define TIME_ADVANCE_IN_SECONDS 0.01

void GameMonitor::addPlayer(const size_t &id, const std::string &name, const Team &team, const Skin &skin) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.addPlayer(id, name, team, skin);
}

void GameMonitor::move(const size_t &id, const Coordinate &displacement) {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::cout << "GameMonitor::move, Entre move" << std::endl;
    this->game.move(id, displacement);
}

void GameMonitor::changeAngle(const size_t &id, const Coordinate &coordinate) {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::cout << "GameMonitor::changeAngle, Entre changeAngle, id:" << id << " dir:("<< coordinate.getInfo().getX() << ", " << coordinate.getInfo().getY() << ") " << std::endl;
    this->game.changeAngle(id, coordinate);
}

void GameMonitor::setWeapon(const size_t &id, const uint8_t &index) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.setWeapon(id, index);
}

std::vector<std::vector<uint8_t>> GameMonitor::getMap() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->game.getMap();
}

void GameMonitor::buy(const size_t &id, const ProductType &product) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.buy(id, product);
}

void GameMonitor::buy(const size_t &id, const ProductType &product, uint16_t amount) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.buy(id, product, amount);
}

void GameMonitor::takeDrop(const size_t &id) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.takeDrop(id);
}

void GameMonitor::attack(const size_t &id) {
    std::lock_guard<std::mutex> lock(this->mutex);
    std::cout << "GameMonitor::attack, estoy atacando, id: "<< (int) id << std::endl;
    this->game.attack(id);
}

void GameMonitor::spawnBomb() {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.spawnBomb();
}

void GameMonitor::deactivateBomb(const size_t &id) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.deactivateBomb(id);
}

GameInfoDTO GameMonitor::getInfo() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->game.getInfo();
}

void GameMonitor::kick(const size_t &id) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.kick(id);
}


void GameMonitor::sendPreSnapshot() {
    GameInfoDTO gameInfo = game.getInfo();
    for ( auto& player : gameInfo.getPlayersInfo() ) {
        std::vector<std::vector<uint8_t>> map = game.getMap();
        PreSnapshot preSnapshot(player.getId(), map);
        this->protocol.sendPreSnapshot(preSnapshot);
    }
}

void GameMonitor::run() {
    this->sendPreSnapshot();
    double time = 0;
    /*----------------------Para debbug------------------------*/
    std::map<size_t, std::vector<double>> movements;
    movements.emplace(0,std::vector<double>());
    movements.emplace(1,std::vector<double>());
    movements.at(0).push_back(304);
    movements.at(0).push_back(48);
    movements.at(1).push_back(272);
    movements.at(1).push_back(112);
    /*--------------------------------------------------------*/
    while (this->should_keep_running()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard lock(this->mutex);
        game.advance(time);
        time += TIME_ADVANCE_IN_SECONDS;
        GameInfoDTO gameInfo = game.getInfo();
        /*----------------------------------------------------Para debbug-----------------------------------------------------------------------------------------------*/
        for (auto& player : gameInfo.getPlayersInfo() ) {
            if (movements.at(player.getId()).at(0) != player.getCoordinate().getX() ||
                movements.at(player.getId()).at(1) != player.getCoordinate().getY()) {
                std::cout << "id: " <<player.getId() << ", name: " << player.getName() << "(" << player.getCoordinate().getX() << ", " << player.getCoordinate().getY() << "), angulo:" << player.getAngle() << std::endl;
                movements.at(player.getId()).clear();
                movements.at(player.getId()).push_back(player.getCoordinate().getX());
                movements.at(player.getId()).push_back(player.getCoordinate().getY());
                }
        }
        /*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        if (gameInfo.getStatus() == TERRORISTS_WIN || gameInfo.getStatus() == COUNTERS_WIN) {
            time = 0;
            game.nextRound(time);
        }
        this->protocol.sendSnapshot(gameInfo);
    }
}
