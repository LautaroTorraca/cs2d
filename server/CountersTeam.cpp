//
// Created by lionel on 26/05/25.
//

#include "CountersTeam.h"
#include <ranges>

void CountersTeam::add(const size_t& id, std::shared_ptr<CounterPlayer>& counterPlayer) {
    this->counters.emplace(id, counterPlayer);
}

void CountersTeam::deactivate(size_t id, Positionable& positionable) const {
    if (!this->counters.contains(id)) return;
    this->counters.at(id)->deactivate(positionable);
}

void CountersTeam::reset(Spawner &spawner) {
    this->cemetery.clear();
    for (auto &counter: this->counters | std::views::values) {
        counter->reset();
        std::shared_ptr<Entity> entity = counter;
        spawner.spawnCounter(entity);
    }
}

void CountersTeam::advance(const double &) {
    for (auto &counter: this->counters | std::views::values) {
        counter->signDeath(this->cemetery);
    }
    if (this->cemetery.size() == this->counters.size()) {
        this->finalizable.terroristsWins();
    }
}

void CountersTeam::giveMoney(const uint16_t &money) {
    for ( auto &counter: this->counters | std::views::values) {
        counter->give(money);
    }
}
