//
// Created by lionel on 29/05/25.
//

#ifndef PRIMARYDROP_H
#define PRIMARYDROP_H
#include "ActivedDrop.h"

class DropBox : public Drop {
    std::shared_ptr<Drop> actualDrop;
public:
    DropBox(const uint8_t& index, const std::shared_ptr<Weapon>& weapon, const Position& position) : actualDrop(std::make_shared<ActivedDrop>(index, weapon, position)) {}
    void giveTo(Inventory &inventory) override;
    DropDTO getInfo() override;
    ~DropBox() override = default;
};



#endif //PRIMARYDROP_H
