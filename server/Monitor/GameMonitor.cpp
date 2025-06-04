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
    this->game.move(id, displacement);
}

void GameMonitor::changeAngle(const size_t &id, const Coordinate &coordinate) {
    std::lock_guard<std::mutex> lock(this->mutex);
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
    std::vector<std::vector<uint8_t>> map = game.getMap();
    GameInfoDTO gameInfo = game.getInfo();
    for ( auto& player : gameInfo.getPlayersInfo() ) {
        PreSnapshot preSnapshot(player.getId(), map);
        this->protocol.sendPreSnapshot(preSnapshot);
    }
}

void GameMonitor::run() {
    this->sendPreSnapshot();
    double time = 0;
    while (this->should_keep_running()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard lock(this->mutex);
        game.advance(time);
        time += TIME_ADVANCE_IN_SECONDS;
        GameInfoDTO gameInfo = game.getInfo();
        if (gameInfo.getStatus() == TERRORISTS_WIN || gameInfo.getStatus() == COUNTERS_WIN) {
            time = 0;
            game.nextRound(time);
        }
        this->protocol.sendSnapshot(gameInfo);
    }
}
