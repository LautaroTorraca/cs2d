#pragma once
#include "common/Constants/SnapshotConstants.h"
#include "server/GameInfoDTO.h"

#include "Disconnectable.h"

class InGameProtocolInterface : public Disconnectable {

public:
    ~InGameProtocolInterface() override = default;

  virtual void sendPreSnapshot(const PreSnapshot & preSnapshot) = 0;

  virtual void sendSnapshot(const GameInfoDTO& gameInfo) = 0;

    virtual void sendSnapshot(const GameInfoDTO& gameInfo, const size_t& id) = 0;
};
