//
// Created by lionel on 28/05/25.
//

#ifndef BOMB_H
#define BOMB_H
#include "Addable.h"
#include "Explosive.h"
#include "Finalizable.h"
#include "GenericWeapon.h"
#include "Owner.h"
#include "Weapon.h"


class Bomb : public GenericWeapon, public Addable, public Explosive {
    Finalizable& finalizable;
    double activationDuration;
    double deactivationDuration;
    double activationStartTime;
    double deactivationStartTime;
    double lastDeactivationTime;
    double actualTime;

public:
    explicit Bomb(Finalizable& finalizable, const double& activationDuration, const double& deactivationDuration) :
    finalizable(finalizable),
    activationDuration(activationDuration),
    deactivationDuration(deactivationDuration),
    activationStartTime(0),
    deactivationStartTime(0),
    lastDeactivationTime(0),
    actualTime(0) {}
    ~Bomb() override = default;
    Bomb(Bomb&& other) noexcept;
    void attack(Positionable &positionable, const Position &actualPosition, const double &destination) override;
    void recharge(uint16_t &) override {}
    void addTo(Inventory &inventory) override;
    void advance(const double &actualTime) override;
    void deactivate() override;
    void activate() override;
    void continueActivation(const double& actualTime) override;
    WeaponInfoDTO getInfo() override;
};



#endif //BOMB_H
