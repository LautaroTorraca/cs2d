//
// Created by lionel on 26/05/25.
//

#include "CounterPlayer.h"

void CounterPlayer::deactivate(Positionable& positionable) {
    positionable.deactivate(this->position);
}
