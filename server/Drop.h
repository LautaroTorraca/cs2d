//
// Created by lionel on 29/05/25.
//

#ifndef DROP_H
#define DROP_H
#include "DropDTO.h"
#include "Inventory.h"

class Drop {
public:
    virtual void giveTo(Inventory& inventory) = 0;
    virtual DropDTO getInfo() = 0;
    virtual ~Drop() = default;
};
#endif  // DROP_H
