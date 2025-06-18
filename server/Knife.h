//
// Created by lionel on 28/05/25.
//

#ifndef KNIFE_H
#define KNIFE_H
#include "DistanceWeapon.h"


class Knife : public DistanceWeapon {
    double knifeMinDamage;
    double knifeMaxDamage;
    double knifeSpeed;
    double knifeRange;

public:

    Knife(const double& knifeMinDamage, const double& knifeMaxDamage, const double& knifeSpeed, const double& knifeRange) :
        knifeMinDamage(knifeMinDamage),
        knifeMaxDamage(knifeMaxDamage),
        knifeSpeed(knifeSpeed),
        knifeRange(knifeRange){}

    void attack(Positionable &mover, const Position &actualPosition, const double &destination) override;

    void recharge(uint16_t &) override {}

    WeaponInfoDTO getInfo() override;

    ~Knife() override = default;
};



#endif //KNIFE_H
