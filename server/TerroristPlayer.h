//
// Created by lionel on 26/05/25.
//

#ifndef TERRORISTPLAYER_H
#define TERRORISTPLAYER_H
#include "Player.h"
#include "Owner.h"


class TerroristPlayer : public Player {
    uint8_t actualWeaponIndex;
public:
    TerroristPlayer(const size_t& id, const std::string& name, const Skin& skin, const GameParser& gameParser, DropPlacer& weaponPlacer) : Player(id, name, skin, gameParser, weaponPlacer), actualWeaponIndex(INITIAL_SELECTED_WEAPON_INDEX) {}
    void addBomb(std::shared_ptr<Weapon> &weapon);
    void release(const uint8_t &index) override;
    void reset() override;
};



#endif //TERRORISTPLAYER_H
