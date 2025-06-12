//
// Created by lionel on 02/06/25.
//

#ifndef DISCONNECTABLE_H
#define DISCONNECTABLE_H
#include "server/DTO/DisconnectionDTO.h"

class Disconnectable {
public:
    virtual ~Disconnectable() = default;
    virtual void disconnect(const DisconnectionDTO& disconnectionInfo) = 0;
};

#endif  // DISCONNECTABLE_H
