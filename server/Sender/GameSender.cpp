//
// Created by lionel on 02/06/25.
//

#include "GameSender.h"

#include "common/Constants/SnapshotConstants.h"

#define TIME_ADVANCE_IN_SECONDS 0.01

void GameSender::sendPreSnapshot() {
    std::vector<std::vector<uint8_t>> map = game.getMap();
    GameInfoDTO gameInfo = game.getInfo();
    for ( auto& player : gameInfo.getPlayersInfo() ) {
        PreSnapshot preSnapshot(player.getId(), map);
        this->protocol.sendPreSnapshot(preSnapshot);
    }
}

void GameSender::run() {
    this->sendPreSnapshot();
    double time = 0;
    while (this->should_keep_running()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
