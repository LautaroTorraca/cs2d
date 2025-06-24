//
// Created by lionel on 29/05/25.
//

#include "DropBox.h"

#include "DeactivatedDrop.h"

void DropBox::giveTo(Inventory &inventory) {
    this->actualDrop->giveTo(inventory);
    this->actualDrop = std::make_shared<DeactivatedDrop>();
}

DropDTO DropBox::getInfo() {
    return this->actualDrop->getInfo();
}
