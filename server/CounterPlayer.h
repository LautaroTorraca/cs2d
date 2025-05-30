//
// Created by lionel on 26/05/25.
//

#ifndef COUNTERPLAYER_H
#define COUNTERPLAYER_H
#include "Player.h"


class CounterPlayer : public Player {
public:
    CounterPlayer(const size_t& id, const std::string& name, const GameParser& gameParser, DropPlacer& weaponPlacer) : Player(id, name, gameParser, weaponPlacer) {}

};



#endif //COUNTERPLAYER_H
