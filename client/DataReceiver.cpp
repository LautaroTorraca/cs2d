
#include "DataReceiver.h"

#include <iostream>

#include "Protocol.h"
// #include "SDL_timer.h"
#include "SnapshotConstants.h"
#include "fixedOverWritingQueue.h"

using namespace Client;
DataReceiver::DataReceiver(Protocol& protocol, QueueFixed<Snapshot>& queue):
        protocol(protocol), snapshotQueue(queue) {};


void DataReceiver::run() {
    try {
        while (running) {
            Snapshot snapshot = protocol.receiveSnapshot();
            snapshotQueue.push(snapshot);
            if(snapshot.status == GAME_OVER)
                return;
        }
    } catch (const ClosedQueue&) {
        std::cout << "queue ded\n";
        snapshotQueue.close();
    } catch (...) {
        std::cout << "queue ded and other error\n";
        snapshotQueue.close();
    }
}

void DataReceiver::close() {
    running = false;
}
