//
// Created by lionel on 26/05/25.
//

#include "CountersTeam.h"

void CountersTeam::add(const size_t& id, std::shared_ptr<CounterPlayer>& counterPlayer) {
    this->counters.emplace(id, counterPlayer);
}