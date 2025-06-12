//
// Created by lionel on 26/05/25.
//

#ifndef COUNTERPLAYER_H
#define COUNTERPLAYER_H
#include "Player.h"

#define BOMB_INDEX 3

class CounterPlayer: public Player {
public:
    CounterPlayer(const size_t& id, const std::string& name, const Skin& skin,
                  const GameParser& gameParser, DropPlacer& weaponPlacer):
            Player(id, name, skin, gameParser, weaponPlacer) {
        this->inventory.addBanned(BOMB_INDEX);
    }

    void deactivate(Positionable& positionable);
};


#endif  // COUNTERPLAYER_H
