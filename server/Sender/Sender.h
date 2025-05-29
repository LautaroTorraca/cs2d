
#ifndef SENDER_H
#define SENDER_H

#include <string>

#include "common/socket.h"

class Sender {
public:
  Sender() = default;

  static void send(Socket &socket, std::string data);

  static void bytesChecker(const int &sendBytes);
};

#endif // SENDER_H
