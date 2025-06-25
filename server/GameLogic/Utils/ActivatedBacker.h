//
// Created by lionel on 26/05/25.
//

#ifndef ACTIVATEDBACKER_H
#define ACTIVATEDBACKER_H
#include "GameLogic/Interfaces/Backer.h"


class ActivatedBacker : public Backer {
Position oldPosition;
public:
    ActivatedBacker(Position& position);
    void pushBack(Position &positionToUpdate) override;

};



#endif //ACTIVATEDBACKER_H
