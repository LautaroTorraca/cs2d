//
// Created by lionel on 01/06/25.
//

#ifndef GENERICWEAPON_H
#define GENERICWEAPON_H
#include "Weapon.h"


class GenericWeapon : public Weapon {
protected:
    std::shared_ptr<Owner> owner;
public:
void set(std::shared_ptr<Owner> &owner) override;
};



#endif //GENERICWEAPON_H
