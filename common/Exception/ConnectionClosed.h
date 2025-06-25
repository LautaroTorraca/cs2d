//
// Created by lionel on 23/06/25.
//

#ifndef CONNECTIONCLOSED_H
#define CONNECTIONCLOSED_H

#include <stdexcept>
#include <string>

class ConnectionClosed: public std::runtime_error {
public:
    ConnectionClosed(const ConnectionClosed&) = delete;
    ConnectionClosed& operator=(const ConnectionClosed&) = delete;
    ConnectionClosed(ConnectionClosed&&) noexcept = delete;
    ConnectionClosed& operator=(ConnectionClosed&&) noexcept = delete;
    explicit ConnectionClosed(const std::string& message): runtime_error(message) {}
};


#endif //CONNECTIONCLOSED_H
