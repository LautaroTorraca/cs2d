#pragma once
#include "../Orders/InGameOrder.h"
#include "../Requests/Request.h"

class InGameProtocolInterface {

public:
  virtual InGameOrder movement(const Request &request) = 0;
  virtual InGameOrder shoot(const Request &request) = 0;
  virtual InGameOrder pickUpItem(const Request &request) = 0;
  virtual InGameOrder dropItem(const Request &request) = 0;
  virtual InGameOrder buyAmmo(const Request &request) = 0;
  virtual InGameOrder buyWeapon(const Request &request) = 0;
  virtual InGameOrder switchWeapon(const Request &request) = 0;
  virtual InGameOrder plantBomb(const Request &request) = 0;
  virtual InGameOrder defuseBomb(const Request &request) = 0;
  virtual InGameOrder exit(const Request &request) = 0;

  virtual ~InGameProtocolInterface() = default;
};
