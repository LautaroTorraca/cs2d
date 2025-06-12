//
// Created by lionel on 01/06/25.
//

#ifndef DISCONNECTIONDTO_H
#define DISCONNECTIONDTO_H

struct DisconnectionDTO {
    const size_t clientId;
    DisconnectionDTO(const size_t& clientId): clientId(clientId) {}
};

#endif  // DISCONNECTIONDTO_H
