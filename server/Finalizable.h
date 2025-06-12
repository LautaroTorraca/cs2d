//
// Created by lionel on 30/05/25.
//

#ifndef FINALIZABLE_H
#define FINALIZABLE_H

class Finalizable {
public:
    virtual ~Finalizable() = default;
    virtual void bombHasBeenPlanted() = 0;
    virtual void terroristsWins() = 0;
    virtual void countersWins() = 0;
    virtual void allTerroristsAreDead() = 0;
};

#endif  // FINALIZABLE_H
