

#ifndef READER_H
#define READER_H
#include <cstdint>
#include <string>

#include "common/socket.h"


class Reader {
    Socket& socket;

    void bytesChecker(const int& bytesRead) const;

public:
    explicit Reader(Socket& socket);
    ~Reader() = default;

    [[nodiscard]] uint8_t u8tReader() const;

    uint16_t u16tReader() const;

    [[nodiscard]] std::string stringReader() const;


};



#endif //READER_H
