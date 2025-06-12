#pragma once
#include "common/Constants/SnapshotConstants.h"

#include "Disconnectable.h"
#include "GameInfoDTO.h"

class InGameProtocolInterface: public Disconnectable {

public:
    virtual ~InGameProtocolInterface() = default;

    virtual void sendPreSnapshot(const PreSnapshot& preSnapshot) = 0;

    virtual void sendSnapshot(const GameInfoDTO& gameInfo) = 0;
};
