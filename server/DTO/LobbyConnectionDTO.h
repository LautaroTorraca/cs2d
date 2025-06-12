//
// Created by lionel on 02/06/25.
//

#ifndef SUCCESSLOBBYCONNECTIONDTO_H
#define SUCCESSLOBBYCONNECTIONDTO_H
#include <cstddef>

#include "server/Constants/ConnectionStatus.h"

class LobbyConnectionDTO {
public:
    const size_t id;
    const ConnectionStatus status;
    explicit LobbyConnectionDTO(const size_t& id, const ConnectionStatus& status):
            id(id), status(status){};
};

#endif  // SUCCESSLOBBYCONNECTIONDTO_H
