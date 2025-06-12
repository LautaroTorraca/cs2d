//
// Created by lionel on 29/05/25.
//

#ifndef DEACTIVATEDDROP_H
#define DEACTIVATEDDROP_H
#include "Drop.h"


class DeactivatedDrop: public Drop {
public:
    void giveTo(Inventory&) override {}
    DropDTO getInfo() override;
    ~DeactivatedDrop() override = default;
};


#endif  // DEACTIVATEDDROP_H
