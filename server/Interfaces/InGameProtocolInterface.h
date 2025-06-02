#pragma once
#include "Disconnectable.h"
#include "GameInfoDTO.h"
#include "../Orders/InGameOrder.h"
#include "../Requests/Request.h"

class InGameProtocolInterface : public Disconnectable {

public:
  virtual ~InGameProtocolInterface() = default;

  virtual void sendPreSnapshot(const PreSnapshot & preSnapshot) = 0;

  virtual void sendSnapshot(const GameInfoDTO & gameInfo) = 0;
};
