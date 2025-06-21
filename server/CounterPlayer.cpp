//
// Created by lionel on 26/05/25.
//

#include "CounterPlayer.h"

void CounterPlayer::deactivate(Positionable& positionable) {
    if (this->status == PlayerStatus::DEAD) return;
    std::shared_ptr<Deactivator> deactivator(this, [&](Deactivator*){});
    positionable.deactivate(this->position, deactivator);
}
void CounterPlayer::deactivating() {
    if (this->status == PlayerStatus::DEAD) return;
    this->status = PlayerStatus::DEFUSING;
}

void CounterPlayer::deactivatingStopped() {
    if (this->status == PlayerStatus::DEAD) return;
        this->status = PlayerStatus::LIVING;
}
