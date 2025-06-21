
#include "DataReceiver.h"

#include <iostream>

#include "Protocol.h"
#include "SDL_timer.h"
#include "SnapshotConstants.h"
#include "fixedOverWritingQueue.h"

DataReceiver::DataReceiver(Protocol& protocol, QueueFixed<Snapshot>& queue):
        protocol(protocol), snapshotQueue(queue) {};


void DataReceiver::run() {
    try {
        while (running) {
            Snapshot snapshot = protocol.receiveSnapshot();
            snapshotQueue.push(snapshot);
            // SDL_Delay(500);
        }
    } catch (const ClosedQueue&) {
        std::cout << "queue ded\n";
        snapshotQueue.close();
    } catch (...) {
        std::cout << "queue ded and other error\n";
        snapshotQueue.close();
        return;
    }
}

void DataReceiver::close() {
    running = false;
    protocol.exit();  //  XXX: esto cierra aca tambien? o solo aca?? idk
}
