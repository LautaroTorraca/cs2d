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
    const std::string info;
    LobbyConnectionDTO(const size_t& id, const ConnectionStatus& status, const std::string& info):
            id(id), status(status), info(info) {}
};

#endif  // SUCCESSLOBBYCONNECTIONDTO_H
