
#include "Sender.h"

#include <stdexcept>

void Sender::bytesChecker(const int& bytesRead) {
    if (bytesRead == 0) {
        throw std::runtime_error("Connection closed"); //TODO HACERLO mas FANCY (socket cerrado)
    }
}

void Sender::send(Socket &socket, std::string data) {
    const uint16_t dataLength = data.length();

    int sendBytes = socket.sendall(&dataLength, sizeof(dataLength));
    Sender::bytesChecker(sendBytes);

    sendBytes = socket.sendall(&data, sizeof(data));
    Sender::bytesChecker(sendBytes);
}

