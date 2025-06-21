//
// Created by lionel on 21/06/25.
//

#pragma once

class Deactivator {
    public:
    virtual ~Deactivator() = default;
    virtual void deactivating() = 0;
    virtual void deactivatingStopped() = 0;
};
