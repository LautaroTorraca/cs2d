
#include "DataReceiver.h"

#include <iostream>

#include "Protocol.h"
#include "SnapshotConstants.h"
#include "fixedOverWritingQueue.h"

DataReceiver::DataReceiver(Protocol& protocol, QueueFixed<Snapshot>& queue):
        protocol(protocol), snapshotQueue(queue) {};


void DataReceiver::run() {
    try {
        while (true) {
            Snapshot snapshot = protocol.receiveSnapshot();
            snapshotQueue.push(snapshot);
            std::cout << "puchie\n";
        }
    } catch (const ClosedQueue&) {
        std::cout << "queue ded\n";
        snapshotQueue.close();
    }
}
