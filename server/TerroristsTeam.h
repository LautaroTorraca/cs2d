//
// Created by lionel on 26/05/25.
//

#ifndef TERRORISTSTEAM_H
#define TERRORISTSTEAM_H
#include <map>
#include <memory>

#include "TerroristPlayer.h"


class TerroristsTeam {
    std::map<size_t, std::shared_ptr<TerroristPlayer>> terrorists;
    public:
    void add(const size_t& id, std::shared_ptr<TerroristPlayer>& terroristPlayer);

};



#endif //TERRORISTSTEAM_H
