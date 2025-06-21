#pragma once
#include <QString>
#include "server/Team.h"

class TeamMapper {
public:
    static QString toString(Team team);

    static Team fromString(const QString& teamStr);
};

