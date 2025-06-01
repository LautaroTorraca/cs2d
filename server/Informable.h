//
// Created by lionel on 31/05/25.
//

#ifndef INFORMABLE_H
#define INFORMABLE_H

template<typename T>
class Informable {
public:
    virtual ~Informable() = default;

    virtual T getInfo() = 0;
};

#endif //INFORMABLE_H
