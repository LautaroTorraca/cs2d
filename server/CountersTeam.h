//
// Created by lionel on 26/05/25.
//

#ifndef COUNTERTEAM_H
#define COUNTERTEAM_H
#include <map>

#include "CounterPlayer.h"

class CountersTeam {
    std::map<size_t, std::shared_ptr<CounterPlayer>> counters;
public:
    void add(const size_t& id, std::shared_ptr<CounterPlayer>& counterPlayer);

};

#endif //COUNTERTEAM_H
