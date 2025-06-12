//
// Created by lionel on 26/05/25.
//

#ifndef COUNTERTEAM_H
#define COUNTERTEAM_H
#include <map>

#include "CounterPlayer.h"
#include "Finalizable.h"
#include "Spawner.h"

class CountersTeam: public Advancer {
    Finalizable& finalizable;
    std::map<size_t, std::shared_ptr<CounterPlayer>> counters;
    std::map<size_t, Player&> cemetery;

public:
    explicit CountersTeam(Finalizable& finalizable): finalizable(finalizable) {}
    void add(const size_t& id, std::shared_ptr<CounterPlayer>& counterPlayer);
    void deactivate(size_t id, Positionable& positionable) const;
    void reset(Spawner& spawner);
    void advance(const double& actualTime) override;

    void giveMoney(const uint16_t& money);

    void kickOut(const size_t& id);

    void clear();
};

#endif  // COUNTERTEAM_H
