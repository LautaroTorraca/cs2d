//
// Created by lionel on 28/05/25.
//

#ifndef KNIFE_H
#define KNIFE_H
#include "Weapon.h"


class Knife : public Weapon {
    double knifeMinDamage;
    double knifeMaxDamage;
    double knifeSpeed;
    double knifeRange;

public:

    Knife(const double& knifeMinDamage, const double& knifeMaxDamage, const double& knifeSpeed, const double& knifeRange) :
        knifeMinDamage(knifeMinDamage),
        knifeMaxDamage(knifeMaxDamage),
        knifeSpeed(knifeSpeed),
        knifeRange(knifeRange) {}

    void attack(Positionable &mover, const Position &actualPosition, const Coordinate &destination) override;

    void recharge(uint16_t &amount) override;

    WeaponInfoDTO getInfo() override;

    ~Knife() override = default;
};



#endif //KNIFE_H
