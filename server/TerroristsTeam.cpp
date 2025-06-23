//
// Created by lionel on 26/05/25.
//

#include "TerroristsTeam.h"

#include "Randomizator.h"
#include <ranges>

void TerroristsTeam::add(const size_t &id, std::shared_ptr<TerroristPlayer> &terroristPlayer) {
    this->terrorists.emplace(id, terroristPlayer);
}

void TerroristsTeam::spawnBomb(std::shared_ptr<Weapon>& bomb) {
    if (this->terrorists.empty()) return;
    Randomizator randomizer;
    int selectedIndex = randomizer.getRandom(this->terrorists.size() - 1);
    auto selectedPlayer = std::next(this->terrorists.begin(), selectedIndex)->second;
    selectedPlayer->addBomb( bomb);
}

void TerroristsTeam::reset(Spawner & spawner) {
    this->cemetery.clear();
    for (auto &terrorist: this->terrorists | std::views::values) {
        terrorist->reset();
        std::shared_ptr<Entity> entity = terrorist;
        spawner.spawnTerrorist(entity);
    }
}

void TerroristsTeam::advance(const double &) {
    for (auto &counter: this->terrorists | std::views::values) {
        counter->signDeath(this->cemetery);
    }
    if (this->cemetery.size() == this->terrorists.size()) {
        this->finalizable.allTerroristsAreDead();
    }
}

void TerroristsTeam::giveMoney(const uint16_t &money) {
    for ( auto &counter: this->terrorists | std::views::values) {
        counter->give(money);
    }
}

void TerroristsTeam::kickOut(const size_t &id) {
    if (this->terrorists.contains(id)) {
        this->terrorists.erase(id);
    }
}

void TerroristsTeam::clear() {
    this->terrorists.clear();
    this->cemetery.clear();
}
