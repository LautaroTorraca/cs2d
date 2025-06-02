//
// Created by lionel on 02/06/25.
//

#ifndef GAMESENDER_H
#define GAMESENDER_H
#include "thread.h"
#include "server/Game.h"
#include "server/Interfaces/InGameProtocolInterface.h"


class GameSender : public Thread {
    Game& game;
    InGameProtocolInterface& protocol;
public:
    GameSender(Game& game, InGameProtocolInterface& protocol) : game(game), protocol(protocol) {}

    void sendPreSnapshot();

    void run() override;

};



#endif //GAMESENDER_H
