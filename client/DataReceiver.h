#pragma once

#include "Protocol.h"
#include "SnapshotConstants.h"
#include "fixedOverWritingQueue.h"
#include "thread.h"


class DataReceiver: public Thread {

    bool running = true;
    Protocol& protocol;
    QueueFixed<Snapshot>& snapshotQueue;

public:
    explicit DataReceiver(Protocol& protocol, QueueFixed<Snapshot>& queue);
    void run() override;
    void close();
};
