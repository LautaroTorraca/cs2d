#pragma once
#include <iostream>
#include <string>

#include "MoveConstants.h"
#include "common/Constants/SnapshotConstants.h"
#include "common/socket.h"

class Protocol {
  Socket clientSocket;

public:
  Protocol(const std::string &port, const std::string &hostName);

  void move(const Direction &direction);

  Snapshot receiveSnapshot();

  PreSnapshot receivePreSnapshot();

  virtual ~Protocol() { std::cout << "xd\n"; };
};
