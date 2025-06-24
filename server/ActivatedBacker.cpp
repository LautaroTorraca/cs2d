//
// Created by lionel on 26/05/25.
//

#include "ActivatedBacker.h"

ActivatedBacker::ActivatedBacker(Position &position) {
    this->oldPosition.updateLocationTo(position);
}

void ActivatedBacker::pushBack(Position &positionToUpdate) {
    positionToUpdate.updateLocationTo(oldPosition);
}
