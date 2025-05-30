//
// Created by lionel on 26/05/25.
//

#ifndef TERRORISTPLAYER_H
#define TERRORISTPLAYER_H
#include "Player.h"


class TerroristPlayer : public Player {

public:
    TerroristPlayer(const size_t& id, const std::string& name, const GameParser& gameParser, DropPlacer& weaponPlacer) : Player(id, name, gameParser, weaponPlacer) {}

};



#endif //TERRORISTPLAYER_H
