//
// Created by lionel on 28/05/25.
//

#ifndef WEAPON_H
#define WEAPON_H
#include "DTO/WeaponInfoDTO.h"
#include "GameLogic/Interfaces/Advancer.h"
#include "GameLogic/Interfaces/Informable.h"
#include "GameLogic/Interfaces/Owner.h"
#include "GameLogic/Interfaces/Positionable.h"

class Weapon : public Advancer, public Informable<WeaponInfoDTO>{
public:
    virtual ~Weapon() = default;
    virtual void attack(Positionable &positionable, const Position &actualPosition, const double &direction) = 0;
    virtual void recharge(uint16_t& amount) = 0;
    virtual void set(const std::shared_ptr<Owner>& owner) = 0;
};

#endif //WEAPON_H
