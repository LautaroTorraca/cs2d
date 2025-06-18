#pragma once

#include "Protocol.h"
#include "SnapshotConstants.h"
#include "fixedOverWritingQueue.h"
#include "thread.h"


class DataReceiver: public Thread {

    Protocol& protocol;
    QueueFixed<Snapshot>& snapshotQueue;

public:
    explicit DataReceiver(Protocol& protocol, QueueFixed<Snapshot>& queue);

    virtual void run() override;
};
