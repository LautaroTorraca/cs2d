//
// Created by lionel on 16/06/25.
//

#ifndef UI_H
#define UI_H
#include "server/Protocol/Protocol.h"
#include "thread.h"


class Ui : public Thread {
    bool& serviceStopped;
    Protocol& protocol;
    public:
    explicit Ui(bool& serviceStopped, Protocol& protocol) :
    serviceStopped(serviceStopped), protocol(protocol) {}
    void run() override;

};



#endif //UI_H
