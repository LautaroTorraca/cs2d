//
// Created by lionel on 02/06/25.
//

#include "GameMonitor.h"

#include "common/Constants/SnapshotConstants.h"

#define TIME_ADVANCE_IN_SECONDS 0.01
#define SKIN_BIAS 16
#define TIME_AFTER_GAME_END 5

GameMonitor::GameMonitor(const std::string& gameName,
    GameParser& parser, const uint8_t& rounds,
    InGameProtocolInterface& protocol,
    Queue<std::string>& eraserQueue) :
    gameName(gameName),
    game(parser, rounds),
    rounds(rounds),
    protocol(protocol),
    eraserQueue(eraserQueue) {
    this->skinToTeamTranslator.emplace(Skin::PHOENIX, Team::TERRORISTS);
    this->skinToTeamTranslator.emplace(Skin::L337_KREW, Team::TERRORISTS);
    this->skinToTeamTranslator.emplace(Skin::ARCTIC_AVENGER, Team::TERRORISTS);
    this->skinToTeamTranslator.emplace(Skin::GUERRILLA, Team::TERRORISTS);


    this->skinToTeamTranslator.emplace(Skin::SEAL_FORCE, Team::COUNTER_TERRORISTS);
    this->skinToTeamTranslator.emplace(Skin::GERMAN_GSG9, Team::COUNTER_TERRORISTS);
    this->skinToTeamTranslator.emplace(Skin::UK_SAS, Team::COUNTER_TERRORISTS);
    this->skinToTeamTranslator.emplace(Skin::FRENCH_GIGN, Team::COUNTER_TERRORISTS);

    this->teamToOtherTeamTranslator.emplace(Team::TERRORISTS, Team::COUNTER_TERRORISTS);
    this->teamToOtherTeamTranslator.emplace(Team::COUNTER_TERRORISTS, Team::TERRORISTS);
}

void GameMonitor::addPlayer(const size_t &id, const std::string &name, const Team &team, const Skin &skin) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.addPlayer(id, name, team, skin);
}

void GameMonitor::move(const size_t &id, const Coordinate &displacement) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.move(id, displacement);
}

void GameMonitor::changeAngle(const size_t &id, const double& angle) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->game.changeAngle(id, angle);
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
    GameInfoDTO gameInfo = game.getInfo();
    for ( auto& player : gameInfo.getPlayersInfo() ) {
        std::vector<std::vector<uint8_t>> map = game.getMap();
        std::map<ProductType, double> shopInfo = this->game.getShopInfo();
        PreSnapshot preSnapshot(player.getId(), map, shopInfo);
        this->protocol.sendPreSnapshot(preSnapshot);
    }
}


void GameMonitor::changeTeam(const std::vector<PlayerInfoDTO>& playersInfo) {
    for (auto& player : playersInfo ) {
        Team newTeam = this->teamToOtherTeamTranslator.at(this->skinToTeamTranslator.at(player.getSkin()));
        uint8_t skinId = player.getSkin() < SKIN_BIAS ? player.getSkin() + SKIN_BIAS : player.getSkin() - SKIN_BIAS;
        Skin newSkin = static_cast<Skin>(skinId);
        this->game.addPlayer(player.getId(), player.getName(), newTeam, newSkin);
        this->game.setDeaths(player.getId(), player.getDeaths());
    }
}

void GameMonitor::run() {
    this->sendPreSnapshot();
    double time = 0;
    double endTime = -1;
    GameInfoDTO gameInfo = game.getInfo();
    while ((this->should_keep_running() && gameInfo.getCurrentRound() <= gameInfo.getRounds() && !gameInfo.getPlayersInfo().empty()) || endTime != -1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard lock(this->mutex);
        game.advance(time);
        time += TIME_ADVANCE_IN_SECONDS;
        gameInfo = game.getInfo();
        if (!(gameInfo.getStatus() == BUY_TIME || gameInfo.getStatus() == ON_GOING || gameInfo.getStatus() == BOMB_PLANTED)) {

            if (endTime == -1) {
                endTime = time;
            }

            if (time - endTime < TIME_AFTER_GAME_END) {
                this->protocol.sendSnapshot(gameInfo);
                continue;
            }

            endTime = -1;
            time = 0;
            if (gameInfo.getCurrentRound() == gameInfo.getRounds() / 2) {
                this->game.clearPlayers();
                this->changeTeam(gameInfo.getPlayersInfo());
            }
            game.nextRound(time);
        }
        this->protocol.sendSnapshot(gameInfo);
    }
    gameInfo.setStatus(GAME_OVER);
    this->protocol.sendSnapshot(gameInfo);
    try {
        this->eraserQueue.push(this->gameName);
    } catch (ClosedQueue&) {
        //LOGG the server has ended.A gameMonitor has stopped
    }
}
