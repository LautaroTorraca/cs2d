//
// Created by lionel on 28/05/25.
//

#ifndef WEAPON_H
#define WEAPON_H
#include "Positionable.h"
#include "WeaponInfoDTO.h"
#include "Advancer.h"
#include "Informable.h"
#include "Owner.h"

class Weapon : public Advancer, public Informable<WeaponInfoDTO>{
public:
    virtual ~Weapon() = default;
    virtual void attack(Positionable &positionable, const Position &actualPosition, const double &direction) = 0;
    virtual void recharge(uint16_t& amount) = 0;
    virtual void set(std::shared_ptr<Owner>& owner) = 0;
};

#endif //WEAPON_H
