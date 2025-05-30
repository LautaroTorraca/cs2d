#include "SecondaryAmmo.h"

#define SECONDARY_INDEX 1

void SecondaryAmmo::addTo(Inventory &inventory) {
    inventory.recharge(SECONDARY_INDEX, this->amount);
}
