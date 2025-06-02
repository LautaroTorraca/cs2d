#pragma once
#include <iostream>
#include <string>

#include "MoveConstants.h"
#include "common/Constants/SnapshotConstants.h"

class ProtocolTesting {

  std::string portDummy;
  std::string hostDummy;
  Snapshot gameSnapshot;
  PreSnapshot gamePreSnapshot;

public:
  ProtocolTesting(const std::string &port, const std::string &hostName);

  void move(const Direction &direction);
  void angle(double angleInDegree);

  Snapshot receiveSnapshot();

  PreSnapshot receivePreSnapshot();

  virtual ~ProtocolTesting() { std::cout << "xd\n"; };
};
