
#include "Reader.h"

#include <stdexcept>
#include <string>
#include <vector>

Reader::Reader(Socket &socket) : socket(socket) {}

void Reader::bytesChecker(const int &bytesRead) const {
  if (bytesRead == 0) {
    throw std::runtime_error(
        "Connection closed"); // TODO HACERLO mas FANCY (socket cerrado)
  }
}

uint8_t Reader::u8tReader() const {
  uint8_t result;
  int bytesRead = socket.recvall(&result, sizeof(result));
  this->bytesChecker(bytesRead);
  return result;
}

std::string Reader::stringReader() const {
  uint8_t nameLength = 0;

  int bytesRead = socket.recvall(&nameLength, sizeof(nameLength));
  this->bytesChecker(bytesRead);

  std::vector<char> buffer(nameLength);
  bytesRead = socket.recvall(buffer.data(), nameLength);
  this->bytesChecker(bytesRead);

  std::string str(buffer.begin(), buffer.end());
  return str;
}
