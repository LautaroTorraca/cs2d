#pragma once
#include "Disconnectable.h"
#include "GameInfoDTO.h"
#include "common/Constants/SnapshotConstants.h"

class InGameProtocolInterface : public Disconnectable {

public:
    ~InGameProtocolInterface() override = default;

  virtual void sendPreSnapshot(const PreSnapshot & preSnapshot) = 0;

  virtual void sendSnapshot(const GameInfoDTO& gameInfo) = 0;
};
