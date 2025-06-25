//
// Created by lionel on 16/06/25.
//

#ifndef UI_H
#define UI_H
#include "server/Protocol/Protocol.h"
#include "thread.h"


class Ui : public Thread {
    Protocol& protocol;
    public:
    explicit Ui(Protocol& protocol) :
    protocol(protocol) {}
    void run() override;

};



#endif //UI_H
