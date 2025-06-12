//
// Created by lionel on 26/05/25.
//

#include "TerroristPlayer.h"

#include "CounterPlayer.h"

void TerroristPlayer::addBomb(std::shared_ptr<Weapon>& weapon) {
    this->inventory.add(BOMB_INDEX, weapon);
}

void TerroristPlayer::release(const uint8_t& index) { this->inventory.erase(index); }

void TerroristPlayer::reset() {
    Player::reset();
    this->inventory.erase(BOMB_INDEX);
}
