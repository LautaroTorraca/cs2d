//
// Created by lionel on 01/06/25.
//

#include "GenericWeapon.h"

void GenericWeapon::set(std::shared_ptr<Owner> &owner) {
    this->owner = owner;
}
