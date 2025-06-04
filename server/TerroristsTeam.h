//
// Created by lionel on 26/05/25.
//

#ifndef TERRORISTSTEAM_H
#define TERRORISTSTEAM_H
#include <map>
#include <memory>
#include "TerroristPlayer.h"
#include "Finalizable.h"
#include "Spawner.h"
#include "Bomb.h"


class TerroristsTeam : public Advancer {
    std::map<size_t, std::shared_ptr<TerroristPlayer>> terrorists;
    Finalizable& finalizable;
    std::map<size_t, Player&> cemetery;
    public:
    explicit TerroristsTeam(Finalizable& finalizable) : finalizable(finalizable) {}
    void add(const size_t& id, std::shared_ptr<TerroristPlayer>& terroristPlayer);
    void spawnBomb(std::shared_ptr<Weapon> &bomb);

    void reset(Spawner & spawner);

    void advance(const double &actualTime) override;

    void giveMoney(const uint16_t& money);

    void kickOut(const size_t& id);

    void clear();
};



#endif //TERRORISTSTEAM_H
