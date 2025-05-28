#pragma once
#include <string>

#include "../Constants/MoveConstants.h"
#include "common/socket.h"
#include "server/Constants/SnapshotConstants.h"


class Protocol {
    Socket clientSocket;

public:
    Protocol(const std::string& port, const std::string& hostName);

    void move(const Direction& direction);

    Snapshot receiveSnapshot();

    PreSnapshot receivePreSnapshot();

    virtual ~Protocol();

};


