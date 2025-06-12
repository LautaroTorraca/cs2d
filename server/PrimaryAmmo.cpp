//
// Created by lionel on 28/05/25.
//

#include "PrimaryAmmo.h"

#define PRIMARY_INDEX 2

void PrimaryAmmo::addTo(Inventory& inventory) { inventory.recharge(PRIMARY_INDEX, this->amount); }
