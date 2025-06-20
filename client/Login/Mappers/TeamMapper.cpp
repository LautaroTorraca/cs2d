#include "TeamMapper.h"

QString TeamMapper::toString(Team team) {
    if (team == Team::COUNTER_TERRORISTS) {
        return "CT";
    } else {
        return "TT";
    }
}

Team TeamMapper::fromString(const QString& teamStr) {
    if (teamStr == "CT") {
        return Team::COUNTER_TERRORISTS;
    } else {
        return Team::TERRORISTS;
    }
}
