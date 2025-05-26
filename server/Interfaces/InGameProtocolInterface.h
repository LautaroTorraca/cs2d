#pragma once
#include "../Orders/InGameOrder.h"
#include "../Requests/Request.h"

class InGameProtocolInterface {

public:

    virtual InGameOrder movementHandler(const Request& request);
    virtual InGameOrder shootHandler(const Request& request);
    virtual InGameOrder pickUpItemHandler(const Request& request);
    virtual InGameOrder dropItemHandler(const Request& request);
    virtual InGameOrder buyAmmoHandler(const Request& request);
    virtual InGameOrder buyWeaponHandler(const Request& request);
    virtual InGameOrder switchWeaponHandler(const Request& request);
    virtual InGameOrder plantBombHandler(const Request& request);
    virtual InGameOrder defuseBombHandler(const Request& request);
    virtual InGameOrder exitHandler(const Request& request);

    virtual ~InGameProtocolInterface() = default;
};
