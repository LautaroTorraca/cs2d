//
// Created by lionel on 26/05/25.
//

#include "TerroristsTeam.h"

void TerroristsTeam::add(const size_t &id, std::shared_ptr<TerroristPlayer> &terroristPlayer) {
    this->terrorists.emplace(id, terroristPlayer);
}
