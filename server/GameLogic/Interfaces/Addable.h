//
// Created by lionel on 28/05/25.
//

#ifndef ADDABLE_H
#define ADDABLE_H
#include "Inventory.h"

class Addable {
    public:
    virtual ~Addable() = default;

    virtual void addTo(Inventory& inventory) = 0;

};
#endif //ADDABLE_H
